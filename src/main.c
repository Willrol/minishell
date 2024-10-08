/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:39:34 by aditer            #+#    #+#             */
/*   Updated: 2024/10/08 09:29:52 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "parse_cmd.h"

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
	free(path);
	path = ft_strdup(split[1]);
	ft_free_tab(split);
	close(fd);
	return (path);
}

int	main(int argc, char **argv, char **envp)
{
	t_list		*env;
	t_list		*token;
	t_minishell	minishell;
	t_parse_cmd	*cmd;
	char		*input;
	char		*pwd;

	(void)argc;
	(void)argv;
	minishell.exit_status = 0;
	minishell.username = get_username();
	minishell.path = get_path();
	env = init_env(envp);
	if (!env)
	{
		pwd = getcwd(NULL, 0);
		add_env(&env, "PWD", pwd);
		free(pwd);
		add_env(&env, "SHLVL", "0");
		add_env(&env, "_", "/usr/bin/env");
	}
	while (1)
	{
		input = ft_strtrim(read_input(env, minishell), " ");
		token = lexer(input);
		if (!token)
		{
			free(input);
			continue ;
		}
		cmd = init_parser_cmd(token);
		minishell.cmd = cmd;
		free_token_list(token);
		free(input);
		expand(cmd, env, minishell);
		// print_parser_cmd(cmd);
		search_here_doc(env, &minishell, cmd);
		execution(env, &minishell, cmd);
		unlink_here_doc(cmd);
		free_parse_cmd(cmd);
	}
	free(minishell.username);
	free(minishell.path);
	// print_env(env);
	free_env(env);
	return (0);
}
