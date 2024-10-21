/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:15:32 by aditer            #+#    #+#             */
/*   Updated: 2024/10/21 18:34:07 by aditer           ###   ########.fr       */
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

void	error_exec(char *str, int error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	if (error == CMD_NFOUND)
		ft_putstr_fd("command not found", 2);
	else if (error == IS_DIR)
		ft_putstr_fd("Is a directory", 2);
	else
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
	shell->fd_save_in = -1;
	shell->fd_save_out = -1;
}

int	test_path(char *path)
{
	if (access(path, F_OK | X_OK) == -1)
		return (CMD_NFOUND);
	return (SUCCESS);
}

bool	is_dir(char *cmd)
{
	struct stat	path_stat;

	if (stat(cmd, &path_stat) == -1)
		return (false);
	return (S_ISDIR(path_stat.st_mode));
}
