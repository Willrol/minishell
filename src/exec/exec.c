/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:08:22 by aditer            #+#    #+#             */
/*   Updated: 2024/10/04 12:53:32 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	child_process(t_list *env, t_minishell *shell, t_parse_cmd *cmd)
{
	int	ret;

	ret = 0;
	if (shell->pipe_fd[READ] != -1)
		close(shell->pipe_fd[READ]);
	if (shell->prev_pipe_fd_out != -1)
	{
		dup2(shell->prev_pipe_fd_out, STDIN_FILENO);
		close(shell->prev_pipe_fd_out);
	}
	if (shell->pipe_fd[WRITE] != -1)
	{
		dup2(shell->pipe_fd[WRITE], STDOUT_FILENO);
		close(shell->pipe_fd[WRITE]);
	}
	if (handle_redirection(shell, cmd) == FAILURE)
	{
		free_child(env, shell);
		exit(1);
	}
	if (cmd->value != NULL)
		ret = do_command(env, shell, cmd);
	free_child(env, shell);
	exit(ret);
}

void	parent_process(t_list *env, t_minishell *shell, t_parse_cmd *cmd)
{
	int	status;

	(void)env;
	if (shell->prev_pipe_fd_out != -1)
		close(shell->prev_pipe_fd_out);
	if (shell->pipe_fd[WRITE] != -1)
		close(shell->pipe_fd[WRITE]);
	shell->prev_pipe_fd_out = shell->pipe_fd[READ];
	shell->pipe_fd[READ] = -1;
	shell->pipe_fd[WRITE] = -1;
	if (cmd->next == NULL)
	{
		waitpid(cmd->pid, &status, 0);
		if (WIFEXITED(status))
		{
			shell->exit_status = WEXITSTATUS(status);
		}
		else
			shell->exit_status = 1;
	}
}

void	do_fork(t_list *env, t_minishell *shell, t_parse_cmd *cmd)
{
	if (cmd->next != NULL)
	{
		if (pipe(shell->pipe_fd) == -1)
		{
			ft_putstr_fd("pipe failed\n", 2);
			return ;
		}
	}
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		ft_putstr_fd("fork failed\n", 2);
		return ;
	}
	if (cmd->pid == 0)
	{
		child_process(env, shell, cmd);
	}
	else
	{
		parent_process(env, shell, cmd);
	}
}

int	execution(t_list *env, t_minishell *shell, t_parse_cmd *cmd)
{
	bool		has_pipe;
	t_parse_cmd	*tmp;

	tmp = cmd;
	has_pipe = (tmp->next != NULL);
	set_fd(shell);
	while (tmp)
	{
		if (!has_pipe && tmp->value != NULL && is_a_builtin(tmp) == SUCCESS)
			exec_solo_builtin(env, shell, tmp);
		else
			do_fork(env, shell, tmp);
		tmp = tmp->next;
	}
	while (wait(NULL) > 0)
		;
	return (SUCCESS);
}
