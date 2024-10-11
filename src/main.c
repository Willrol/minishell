/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rderkaza <rderkaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:39:34 by aditer            #+#    #+#             */
/*   Updated: 2024/10/11 15:40:11 by rderkaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "parse_cmd.h"

int		g_sigflag = 0;

char	*read_input(t_list *env, t_minishell shell)
{
	char	*line;

	line = readline("minishell$ ");
	if (!line)
	{
		ft_putstr_fd("exit\n", 1);
		free(shell.username);
		free(shell.path);
		free_env(env);
		exit(0);
	}
	add_history(line);
	return (line);
}

char	*get_path(void)
{
	char	*path;
	char	**split;
	int		fd;

	fd = open("/etc/environment", O_RDONLY);
	if (fd == -1)
		return (NULL);
	path = get_next_line(fd);
	split = ft_split(path, '"');
	if (!split)
	{
		free(path);
		close(fd);
		return (NULL);
	}
	free(path);
	path = ft_strdup(split[1]);
	ft_free_tab(split);
	close(fd);
	return (path);
}

void	handle(int sig)
{
	g_sigflag = sig;
}

void	handle_sigint(int sig)
{
	g_sigflag = sig;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	g_sigflag = sig;
	ft_putstr_fd("Quit (core dumped)\n", 1);
}

void	add_shlvl(t_list *env)
{
	t_list	*shlvl;
	char	*shlvl_str;
	int		shlvl_int;

	shlvl = search_env(env, "SHLVL");
	if (!shlvl)
		return ;
	shlvl_int = ft_atoi(((t_env *)shlvl->content)->content);
	shlvl_int++;
	shlvl_str = ft_itoa(shlvl_int);
	if (!shlvl_str)
		return ;
	free(((t_env *)shlvl->content)->content);
	((t_env *)shlvl->content)->content = shlvl_str;
}

int	main(const int argc, const char **argv, char **envp)
{
	t_list		*env;
	t_list		*token;
	t_minishell	shell;
	t_parse_cmd	*cmd;
	char		*input;
	char		*pwd;
	char		*new_input;

	env = NULL;
	(void)argv;
	if (argc != 1)
		return (1);
	ft_bzero(&shell, sizeof(t_minishell));
	ft_bzero(&token, sizeof(t_list));
	shell.exit_status = 0;
	shell.username = get_username();
	shell.path = get_path();
	if (!shell.username || !shell.path)
		error_malloc(&shell, NULL);
	if (!envp || !*envp)
	{
		pwd = getcwd(NULL, 0);
		if (add_env(&env, "PWD", pwd) == FAILURE)
			error_malloc(&shell, env);
		free(pwd);
		if (add_env(&env, "SHLVL", "0") == FAILURE)
			error_malloc(&shell, env);
		if (add_env(&env, "_", "/usr/bin/env") == FAILURE)
			error_malloc(&shell, env);
	}
	else
		env = init_env(&shell, envp, -1);
	add_shlvl(env);
	while (true)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		shell.cmd = NULL;
		input = read_input(env, shell);
		new_input = ft_strtrim(input, " ");
		free(input);
		if (!new_input)
			error_malloc(&shell, env);
		token = lexer(new_input, 0);
		cmd = init_parser_cmd(token);
		if (cmd == NULL)
		{
			free_token_list(token);
			free(new_input);
			error_malloc(&shell, env);
		}
		shell.cmd = cmd;
		free_token_list(token);
		free(new_input);
		expand(cmd, env, &shell);
		search_here_doc(env, &shell, cmd);
		signal(SIGINT, handle);
		signal(SIGQUIT, SIG_IGN);
		execution(env, &shell, cmd);
		unlink_here_doc(cmd);
		free_parse_cmd(cmd);
	}
	free_shell(&shell, env);
	return (0);
}
