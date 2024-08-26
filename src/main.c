/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:39:34 by aditer            #+#    #+#             */
/*   Updated: 2024/08/26 15:22:48 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*read_input(void)
{
	char	*line;

	line = readline("minishell$ ");
	if (!line)
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	// add_history(line);
	printf("%s\n", line);
	free(line);
	return (line);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*env;

	(void)argc;
	(void)argv;
	env = init_env(envp);
	if (!env)
		return (EXIT_FAILURE);
	print_env(env);
	add_env(&env, "TEST=", "SALOPETTE");
	printf("//////////////////////////////////////////////////:\n");
	add_env(&env, "TEST=", "super SALOPETTE");
	add_env(&env, "TEST2=", "super PATATE");
	print_env(env);
	printf("//////////////////////////////////////////////////:\n");
	remove_env(&env, "TEST=eaza");
	print_env(env);
	free_env(env);
	return (0);
}
