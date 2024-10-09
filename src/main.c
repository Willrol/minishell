/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:39:34 by aditer            #+#    #+#             */
/*   Updated: 2024/10/09 17:16:42 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "parse_cmd.h"

int sigflag = 0;

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

void	quith(int sig)
{
	if (sig == SIGINT)
	{
    sigflag = 1;
    rl_done = 1;
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		sigflag = 0;
		
	}
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
	if (!envp)
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
		env = init_env(&shell, envp);
	while (true)
	{
		signal(SIGINT, quith);
		signal(SIGQUIT, quith);
		shell.cmd = NULL;
		input = read_input(env, shell);
		new_input = ft_strtrim(input, " ");
		free(input);
		if (!new_input)
			error_malloc(&shell, env);
		token = lexer(new_input);
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
		execution(env, &shell, cmd);
		unlink_here_doc(cmd);
		free_parse_cmd(cmd);
	}
	free_shell(&shell, env);
	return (0);
}
