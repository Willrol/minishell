/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rderkaza <rderkaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:15:32 by aditer            #+#    #+#             */
/*   Updated: 2024/10/11 15:37:58 by rderkaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cmd.h"

void	free_child(t_list *env, t_minishell *shell)
{
	free_env(env);
	free_parse_cmd(shell->cmd);
	if (shell->username)
		free(shell->username);
	if (shell->path)
		free(shell->path);
}

void	error_exec(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

void	set_fd(t_minishell *shell)
{
	shell->pipe_fd[READ] = -1;
	shell->pipe_fd[WRITE] = -1;
	shell->prev_pipe_fd_out = -1;
	shell->fd_in = -1;
	shell->fd_out = -1;
	shell->fd_save = -1;
}
