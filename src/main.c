/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:39:34 by aditer            #+#    #+#             */
/*   Updated: 2024/09/17 14:09:22 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse_cmd.h"

char	*read_input(t_list *env)
{
	char	*line;

	line = readline("minishell$ ");
	if (!line)
	{
		ft_putstr_fd("exit\n", 1);
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
	t_parse_cmd	*cmd;
	char		*input;

	(void)argc;
	(void)argv;
	env = init_env(envp);
	if (!env)
		return (EXIT_FAILURE);
	while (1)
	{
		input = ft_strtrim(read_input(env), " ");
		if (strncmp(input, "exit", 4) == 0)
		{
			free(input);
			break ;
		}
		token = lexer(input);
		cmd = init_parser_cmd(token);
		expand(cmd, env);
		print_parser_cmd(cmd);
		free(input);
		free_token_list(token);
		free_parse_cmd(cmd);
	}
	// print_env(env);
	free_env(env);
	return (0);
}
