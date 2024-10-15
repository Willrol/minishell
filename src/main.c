/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:39:34 by aditer            #+#    #+#             */
/*   Updated: 2024/10/15 17:31:24 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "parse_cmd.h"

int	g_sigflag = 0;

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
