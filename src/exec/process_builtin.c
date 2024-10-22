/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 08:10:19 by aditer            #+#    #+#             */
/*   Updated: 2024/10/22 10:08:12 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_a_builtin(t_parse_cmd *cmd)
{
	if (!ft_strcmp(cmd->value, "echo"))
		return (SUCCESS);
	if (!ft_strcmp(cmd->value, "cd"))
		return (SUCCESS);
	if (!ft_strcmp(cmd->value, "pwd"))
		return (SUCCESS);
	if (!ft_strcmp(cmd->value, "export"))
		return (SUCCESS);
	if (!ft_strcmp(cmd->value, "unset"))
		return (SUCCESS);
	if (!ft_strcmp(cmd->value, "env"))
		return (SUCCESS);
	if (!ft_strcmp(cmd->value, "exit"))
		return (SUCCESS);
	return (FAILURE);
}

int	exec_builtin(t_minishell *shell, t_parse_cmd *cmd)
{
	if (!ft_strcmp(cmd->value, "echo"))
		return (echo(cmd->argc, cmd->argv));
	if (!ft_strcmp(cmd->value, "cd"))
		return (cd(cmd->argc, cmd->argv, *shell->env));
	if (!ft_strcmp(cmd->value, "pwd"))
		return (pwd());
	if (!ft_strcmp(cmd->value, "export"))
		return (ft_export(shell->env, shell, cmd->argv));
	if (!ft_strcmp(cmd->value, "unset"))
		return (unset(shell->env, shell, cmd->argv));
	if (!ft_strcmp(cmd->value, "env"))
		return (print_env(*shell->env));
	if (!ft_strcmp(cmd->value, "exit"))
		return (exit_builtin(*shell->env, shell, cmd));
	return (FAILURE);
}

void	exec_solo_builtin(t_minishell *shell, t_parse_cmd *tmp)
{
	int	status;

	shell->fd_save_in = dup(STDIN_FILENO);
	shell->fd_save_out = dup(STDOUT_FILENO);
	status = handle_redirection(shell, tmp);
	if (status != FAILURE)
		shell->exit_status = exec_builtin(shell, tmp);
	else
		shell->exit_status = 1;
	dup2(shell->fd_save_in, STDIN_FILENO);
	dup2(shell->fd_save_out, STDOUT_FILENO);
	if (shell->fd_save_in != -1)
		close(shell->fd_save_in);
	if (shell->fd_save_out != -1)
		close(shell->fd_save_out);
}
