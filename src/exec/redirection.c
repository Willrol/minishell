/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:32:53 by aditer            #+#    #+#             */
/*   Updated: 2024/10/03 13:41:09 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	redirection_in(t_minishell *shell, t_parse_cmd *cmd)
{
	if (shell->fd_in != -1)
		close(shell->fd_in);
	shell->fd_in = open(cmd->redirection->file_name, O_RDONLY);
	if (shell->fd_in == -1)
	{
		error_exec(cmd->redirection->file_name);
		return (FAILURE);
	}
	dup2(shell->fd_in, STDIN_FILENO);
	close(shell->fd_in);
	return (SUCCESS);
}

int	redirection_out(t_minishell *shell, t_parse_cmd *cmd)
{
	if (shell->fd_out != -1)
		close(shell->fd_out);
	shell->fd_out = open(cmd->redirection->file_name,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (shell->fd_out == -1)
	{
		error_exec(cmd->redirection->file_name);
		return (FAILURE);
	}
	dup2(shell->fd_out, STDOUT_FILENO);
	close(shell->fd_out);
	return (SUCCESS);
}

int	redirection_append(t_minishell *shell, t_parse_cmd *cmd)
{
	if (shell->fd_out != -1)
		close(shell->fd_out);
	shell->fd_out = open(cmd->redirection->file_name,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (shell->fd_out == -1)
	{
		error_exec(cmd->redirection->file_name);
		return (FAILURE);
	}
	dup2(shell->fd_out, STDOUT_FILENO);
	close(shell->fd_out);
	return (SUCCESS);
}

int	handle_redirection(t_minishell *shell, t_parse_cmd *cmd)
{
	t_redirection	*redir;

	redir = cmd->redirection;
	while (redir)
	{
		if (redir->type == IN || redir->type == HERE_DOC)
		{
			if (redirection_in(shell, cmd) == FAILURE)
				return (FAILURE);
		}
		else if (redir->type == OUT)
		{
			if (redirection_out(shell, cmd) == FAILURE)
				return (FAILURE);
		}
		else if (redir->type == APPEND)
		{
			if (redirection_append(shell, cmd) == FAILURE)
				return (FAILURE);
		}
		redir = redir->next;
	}
	return (SUCCESS);
}
