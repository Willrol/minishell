/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:26:22 by aditer            #+#    #+#             */
/*   Updated: 2024/10/22 10:20:02 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse_cmd.h"

static void	exit_arg(t_list *env, t_minishell *shell, t_parse_cmd *cmd)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	if (cmd->argv[1][0] == '-' || cmd->argv[1][0] == '+')
		i++;
	while (cmd->argv[1][i])
	{
		if (!isdigit(cmd->argv[1][i]))
		{
			ft_putstr_fd("exit\nminishell: exit: ", 2);
			ft_putstr_fd(cmd->argv[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			free_shell(shell, env);
			exit(2);
		}
		i++;
	}
	status = ft_atoi(cmd->argv[1]);
	free_shell(shell, env);
	exit(status);
}

static int	exit_args(t_list *env, t_minishell *shell, t_parse_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->argv[1][0] == '-' || cmd->argv[1][0] == '+')
		i++;
	while (cmd->argv[1][i])
	{
		if (!isdigit(cmd->argv[1][i]))
		{
			ft_putstr_fd("exit\nminishell: exit: ", 2);
			ft_putstr_fd(cmd->argv[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			free_shell(shell, env);
			exit(2);
		}
		i++;
	}
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	shell->exit_status = 1;
	return (1);
}

int	exit_builtin(t_list *env, t_minishell *shell, t_parse_cmd *cmd)
{
	if (cmd->argc == 1)
	{
		free_shell(shell, env);
		exit(shell->exit_status);
	}
	else if (cmd->argc == 2)
	{
		exit_arg(env, shell, cmd);
		return (SUCCESS);
	}
	else if (cmd->argc > 2)
	{
		return (exit_args(env, shell, cmd));
	}
	return (FAILURE);
}
