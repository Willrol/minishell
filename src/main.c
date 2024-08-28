/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:39:34 by aditer            #+#    #+#             */
/*   Updated: 2024/08/28 14:04:28 by aditer           ###   ########.fr       */
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
	printf("%s\n", line);
	free(line);
	return (line);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*env;

	(void)argc;
	(void)argv;
	lexer("alpha <dqsdq <fd <<  fds| edzq |da\'z<<dsq  > prou\'tdfsdfsd");
	env = init_env(envp);
	if (!env)
		return (EXIT_FAILURE);
	free_env(env);
	return (0);
}
