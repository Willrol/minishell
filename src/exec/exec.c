/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:08:22 by aditer            #+#    #+#             */
/*   Updated: 2024/10/22 13:40:16 by aditer           ###   ########.fr       */
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

void	parent_process(t_minishell *shell, t_parse_cmd *cmd, bool has_pipe)
{
	int	status;

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
		if (WIFSIGNALED(status))
		{
			shell->exit_status = 128 + WTERMSIG(status);
			if (WTERMSIG(status) == SIGQUIT && has_pipe == false)
				ft_putstr_fd("Quit (core dumped)\n", 1);
			if (WTERMSIG(status) == SIGINT && has_pipe == false)
				ft_putstr_fd("\n", 1);
		}
		else if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		else
			shell->exit_status = 1;
	}
}

void	do_fork(t_list *env, t_minishell *shell, t_parse_cmd *cmd,
		bool has_pipe)
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
		signal(SIGINT, handle);
		signal(SIGQUIT, handle_sigquit);
		child_process(env, shell, cmd);
	}
	else
	{
		parent_process(shell, cmd, has_pipe);
	}
}

void	wait_signal(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 1);
		if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd("\n", 1);
	}
}

int	execution(t_list *env, t_minishell *shell, t_parse_cmd *cmd)
{
	bool		has_pipe;
	t_parse_cmd	*tmp;
	int			status;

	tmp = cmd;
	has_pipe = (tmp->next != NULL);
	set_fd(shell);
	while (tmp)
	{
		if (tmp->value == NULL && tmp->redirection == NULL)
		{
			tmp = tmp->next;
			continue ;
		}
		if (!has_pipe && tmp->value != NULL && is_a_builtin(tmp) == SUCCESS)
			exec_solo_builtin(shell, tmp);
		else
			do_fork(env, shell, tmp, has_pipe);
		tmp = tmp->next;
	}
	while (waitpid(-1, &status, 0) > 0)
		wait_signal(status);
	return (SUCCESS);
}
