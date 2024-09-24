/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_a_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rderkaza <rderkaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 08:10:19 by aditer            #+#    #+#             */
/*   Updated: 2024/09/24 16:59:45 by rderkaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cmd.h"
#include "minishell.h"

int	is_a_builtin(t_list *env, t_parse_cmd *cmd)
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
