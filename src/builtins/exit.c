/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:26:22 by aditer            #+#    #+#             */
/*   Updated: 2024/10/04 12:59:42 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse_cmd.h"

static void	exit_arg(t_list *env, t_minishell *shell, t_parse_cmd *cmd)
{
	int	status;

	status = 0;
	if (ft_isdigit(cmd->argv[1][0]) == 0)
	{
		printf("exit\nminishell: exit: %s: numeric argument required\n",
			cmd->argv[1]);
		if (shell->fd_save != -1)
			close(shell->fd_save);
		exit(2);
	}
	else
	{
		status = ft_atoi(cmd->argv[1]);
		free(shell->username);
		free_env(env);
		free_parse_cmd(shell->cmd);
		if (shell->fd_save != -1)
			close(shell->fd_save);
		exit(status);
	}
}

int	exit_builtin(t_list *env, t_minishell *shell, t_parse_cmd *cmd)
{
	if (cmd->argc == 1)
	{
		free_env(env);
		free_parse_cmd(shell->cmd);
		free(shell->username);
		if (shell->fd_save != -1)
			close(shell->fd_save);
		exit(shell->exit_status);
	}
	else if (cmd->argc == 2)
	{
		exit_arg(env, shell, cmd);
		return (SUCCESS);
	}
	else
	{
		printf("exit\nminishell: exit: too many arguments\n");
		shell->exit_status = 1;
		return (FAILURE);
	}
}
