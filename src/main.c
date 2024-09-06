/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:39:34 by aditer            #+#    #+#             */
/*   Updated: 2024/09/06 12:52:28 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_input(void)
{
	char	*line;

	line = readline("minishell$ ");
	add_history(line);
	return (line);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*env;
	char	*input;

	(void)argc;
	(void)argv;
	env = init_env(envp);
	if (!env)
		return (EXIT_FAILURE);
	while (1)
	{
		input = ft_strtrim(read_input(), " ");
		if (strncmp(input, "exit", 4) == 0)
		{
			free(input);
			break ;
		}
		lexer(input);
		free(input);
	}
	// print_env(env);	
	free_env(env);
	return (0);
}
