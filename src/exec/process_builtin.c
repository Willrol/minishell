/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 08:10:19 by aditer            #+#    #+#             */
/*   Updated: 2024/10/04 12:37:37 by aditer           ###   ########.fr       */
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

int	exec_builtin(t_list *env, t_minishell *shell, t_parse_cmd *cmd)
{
	if (!ft_strcmp(cmd->value, "echo"))
		return (echo(cmd->argc, cmd->argv));
	if (!ft_strcmp(cmd->value, "cd"))
		return (cd(cmd->argc, cmd->argv, env));
	if (!ft_strcmp(cmd->value, "pwd"))
		return (pwd());
	if (!ft_strcmp(cmd->value, "export"))
		return (ft_export(&env, cmd->argv));
	if (!ft_strcmp(cmd->value, "unset"))
		return (remove_env(&env, cmd->argv));
	if (!ft_strcmp(cmd->value, "env"))
		return (print_env(env));
	if (!ft_strcmp(cmd->value, "exit"))
		return (exit_builtin(env, shell, cmd));
	return (FAILURE);
}

void	exec_solo_builtin(t_list *env, t_minishell *shell, t_parse_cmd *tmp)
{
	shell->fd_save = dup(STDOUT_FILENO);
	handle_redirection(shell, tmp);
	shell->exit_status = exec_builtin(env, shell, tmp);
	dup2(shell->fd_save, STDOUT_FILENO);
	if (shell->fd_save != -1)
		close(shell->fd_save);
}
