/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:39:34 by aditer            #+#    #+#             */
/*   Updated: 2024/09/25 08:49:37 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_list			*env;
	t_list			*token;
	t_minishell		backup;
	t_parse_cmd		*cmd;
	char			*input;

	(void)argc;
	(void)argv;
	backup.username = get_username();
	backup.path = "/home/aditer/.local/funcheck/host:/home/aditer/bin:\
	/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:\
	/usr/local/games:/snap/bin";
	env = init_env(envp);
	if (!env)
		return (EXIT_FAILURE);
	while (1)
	{
		input = ft_strtrim(read_input(env, backup), " ");
		token = lexer(input);
		if (!token)
		{
			free(input);
			continue ;
		}
		cmd = init_parser_cmd(token);
		expand(cmd, env, backup);
		// print_parser_cmd(cmd);
		execution(env, &backup, cmd);
		free(input);
		free_token_list(token);
		free_parse_cmd(cmd);
	}
	free(backup.username);
	// print_env(env);
	free_env(env);
	return (0);
}
