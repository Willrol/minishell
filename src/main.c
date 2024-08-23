/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:39:34 by aditer            #+#    #+#             */
/*   Updated: 2024/08/23 13:31:43 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	read_input()
{
	char *line;

	line = readline("minishell$ ");
	if (!line)
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	// add_history(line);
	printf("%s\n", line);
	free(line);
}
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	t_list *env;

	env = init_env(envp);
	if (!env)
		return (EXIT_FAILURE);
	print_env(env);
	printf("//////////////////////////////////////////////////:\n");
	add_env(&env, "TEST=", "SALOPETTE");
	printf("//////////////////////////////////////////////////:\n");
	add_env(&env, "TEST=", "super SALOPETTE");
	print_env(env);
	free_env(env);
	return (0);
}
