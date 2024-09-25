/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 08:10:19 by aditer            #+#    #+#             */
/*   Updated: 2024/09/25 17:00:27 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse_cmd.h"

int	is_a_builtin(t_parse_cmd *cmd)
{
	if (!ft_strcmp(cmd->value, "echo"))
		return(SUCCESS);
	if (!ft_strcmp(cmd->value, "cd"))
		return(SUCCESS);
	if (!ft_strcmp(cmd->value, "pwd"))
		return(SUCCESS);
	if (!ft_strcmp(cmd->value, "export"))
		return(SUCCESS);
	if (!ft_strcmp(cmd->value, "unset"))
		return(SUCCESS);
	if (!ft_strcmp(cmd->value, "env"))
		return(SUCCESS);
	// if (!ft_strcmp(cmd->value, "exit"))
	// 	return (exit(cmd->argc, cmd->argv));
	return (FAILURE);
}

int	exec_builtin(t_list *env, t_parse_cmd *cmd)
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
	// if (!ft_strcmp(cmd->value, "exit"))
	// 	return (exit(cmd->argc, cmd->argv));
	return (FAILURE);
}
