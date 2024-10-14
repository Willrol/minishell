/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rderkaza <rderkaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:39:34 by aditer            #+#    #+#             */
/*   Updated: 2024/10/14 16:43:32 by rderkaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "parse_cmd.h"

int			g_sigflag = 0;

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

static void	here_exec(t_minishell *shell, t_parse_cmd *cmd, t_list *env)
{
	if (search_here_doc(env, shell, cmd) == FAILURE)
	{
		unlink_here_doc(cmd);
		free_parse_cmd(cmd);
		return ;
	}
	signal(SIGINT, handle);
	execution(env, shell, cmd);
	unlink_here_doc(cmd);
	free_parse_cmd(cmd);
	return ;
}

void	loop(t_minishell *shell, t_parse_cmd *cmd, t_list *token, t_list *env)
{
	char	*new_input;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	shell->cmd = NULL;
	new_input = init_input(env, *shell);
	if (!new_input)
		error_malloc(shell, env);
	token = lexer(new_input, 0);
	cmd = init_parser_cmd(token);
	if (cmd == NULL)
	{
		free_token_list(token);
		free(new_input);
		error_malloc(shell, env);
	}
	free(new_input);
	shell->cmd = cmd;
	free_token_list(token);
	expand(cmd, env, shell);
	here_exec(shell, cmd, env);
}

int	main(const int argc, const char **argv, char **envp)
{
	t_list		*env;
	t_list		*token;
	t_minishell	shell;
	t_parse_cmd	*cmd;

	env = NULL;
	cmd = NULL;
	(void)argv;
	if (argc != 1)
		return (1);
	ft_bzero(&shell, sizeof(t_minishell));
	ft_bzero(&token, sizeof(t_list));
	init_shell_env(&shell, &env, envp);
	add_shlvl(env);
	while (true)
		loop(&shell, cmd, token, env);
	free_shell(&shell, env);
	return (0);
}

// int	main(const int argc, const char **argv, char **envp)
// {
// 	t_list		*env;
// 	t_list		*token;
// 	t_minishell	shell;
// 	t_parse_cmd	*cmd;
// 	char		*input;
// 	char		*pwd;
// 	char		*new_input;

// 	env = NULL;
// 	(void)argv;
// 	if (argc != 1)
// 		return (1);
// 	ft_bzero(&shell, sizeof(t_minishell));
// 	ft_bzero(&token, sizeof(t_list));
// 	shell.exit_status = 0;
// 	shell.username = get_username();
// 	shell.path = get_path();
// 	if (!shell.username || !shell.path)
// 		error_malloc(&shell, NULL);
// 	if (!envp || !*envp)
// 	{
// 		pwd = getcwd(NULL, 0);
// 		if (add_env(&env, "PWD", pwd) == FAILURE)
// 			error_malloc(&shell, env);
// 		free(pwd);
// 		if (add_env(&env, "SHLVL", "0") == FAILURE)
// 			error_malloc(&shell, env);
// 		if (add_env(&env, "_", "/usr/bin/env") == FAILURE)
// 			error_malloc(&shell, env);
// 	}
// 	else
// 		env = init_env(&shell, envp, -1);
// 	add_shlvl(env);
// 	while (true)
// 	{
// 		signal(SIGINT, handle_sigint);
// 		signal(SIGQUIT, SIG_IGN);
// 		shell.cmd = NULL;
// 		input = read_input(env, shell);
// 		new_input = ft_strtrim(input, " ");
// 		free(input);
// 		if (!new_input)
// 			error_malloc(&shell, env);
// 		token = lexer(new_input, 0);
// 		cmd = init_parser_cmd(token);
// 		if (cmd == NULL)
// 		{
// 			free_token_list(token);
// 			free(new_input);
// 			error_malloc(&shell, env);
// 		}
// 		shell.cmd = cmd;
// 		free_token_list(token);
// 		free(new_input);
// 		expand(cmd, env, &shell);
// 		search_here_doc(env, &shell, cmd);
// 		signal(SIGINT, handle);
// 		signal(SIGQUIT, SIG_IGN);
// 		execution(env, &shell, cmd);
// 		unlink_here_doc(cmd);
// 		free_parse_cmd(cmd);
// 	}
// 	free_shell(&shell, env);
// 	return (0);
// }
