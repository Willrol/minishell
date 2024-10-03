/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:39:34 by aditer            #+#    #+#             */
/*   Updated: 2024/10/03 14:53:35 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "parse_cmd.h"

char	*read_input(t_list *env, t_minishell backup)
{
	char	*line;

	line = readline("minishell$ ");
	if (!line)
	{
		ft_putstr_fd("exit\n", 1);
		free(backup.username);
		free_env(env);
		exit(0);
	}
	add_history(line);
	return (line);
}

int	main(int argc, char **argv, char **envp)
{
	t_list		*env;
	t_list		*token;
	t_minishell	minishell;
	t_parse_cmd	*cmd;
	char		*input;

	(void)argc;
	(void)argv;
	minishell.exit_status = 0;
	minishell.username = get_username();
	minishell.path = "/home/aditer/.local/funcheck/host:/home/aditer/bin:\
	/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:\
	/usr/local/games:/snap/bin";
	env = init_env(envp);
	if (!env)
		return (EXIT_FAILURE);
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
	// print_env(env);
	free_env(env);
	return (0);
}
