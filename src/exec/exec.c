/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:08:22 by aditer            #+#    #+#             */
/*   Updated: 2024/09/30 12:01:36 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse_cmd.h"

char	*exec(t_list *env, t_parse_cmd *cmd)
{
	t_list	*path_node;
	char	*path;
	char	**split_path;
	int		i;

	path_node = search_env(env, "PATH");
	path = ft_strdup(((t_env *)path_node->content)->content);
	i = 0;
	if (path)
	{
		split_path = ft_split(path, ':');
		while (split_path[i])
		{
			free(path);
			path = ft_strjoin3(split_path[i], "/", cmd->value);
			if (access(path, F_OK | X_OK) == 0)
				return (ft_free_tab(split_path), path);
			i++;
		}
		ft_free_tab(split_path);
	}
	return (path);
}

int	exec_command(t_list *env, t_parse_cmd *cmd)
{
	char	*path;
	char	**env_tab;

	path = exec(env, cmd);
	env_tab = get_env_tab(env);
	if (execve(path, cmd->argv, env_tab) == FAILURE)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->value, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		free(path);
		ft_free_tab(env_tab);
		return (126);
	}
	return (SUCCESS);
}

void	child_process(t_list *env, t_minishell *shell, t_parse_cmd *cmd)
{
	int	ret;

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
	if (shell->pipe_fd[READ] != -1)
		close(shell->pipe_fd[READ]);

	if (is_a_builtin(cmd) == SUCCESS)
		ret = exec_builtin(env, cmd);
	else
		ret = exec_command(env, cmd);
	free_env(env);
	free_parse_cmd(shell->cmd);
	free(shell->username);
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

void	set_fd(t_minishell *shell)
{
	shell->pipe_fd[READ] = -1;
	shell->pipe_fd[WRITE] = -1;
	shell->prev_pipe_fd_out = -1;
	shell->fd_in = -1;
	shell->fd_out = -1;
}

int	execution(t_list *env, t_minishell *shell, t_parse_cmd *cmd)
{
	bool has_pipe;
	t_parse_cmd *tmp;

	(void)shell;
	if (!cmd->value)
		return (SUCCESS);
	tmp = cmd;
	has_pipe = (tmp->next != NULL);

	set_fd(shell);
	while (tmp)
	{
		if (!has_pipe && is_a_builtin(tmp) == SUCCESS)
		{
			shell->exit_status = exec_builtin(env, tmp);
		}
		else
		{
			do_fork(env, shell, tmp);
		}
		tmp = tmp->next;
	}
	while (wait(NULL) > 0);
	return (SUCCESS);
}