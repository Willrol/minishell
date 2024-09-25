/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:08:22 by aditer            #+#    #+#             */
/*   Updated: 2024/09/25 18:08:03 by aditer           ###   ########.fr       */
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

	path = exec(env, cmd);
	if (execve(path, cmd->argv, get_env_tab(env)) == FAILURE)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->value, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		free(path);
		return (126);
	}
	return (SUCCESS);
}

void	child_process(t_list *env, t_minishell *shell, t_parse_cmd *cmd)
{
	int	ret;

	if (is_a_builtin(cmd) == SUCCESS)
		ret = exec_builtin(env, cmd);
	else
		ret = exec_command(env, cmd);
	free_env(env);
	free_parse_cmd(cmd);
	free(shell->username);
	exit(ret);
}

void	do_fork(t_list *env,t_minishell *shell, t_parse_cmd *cmd)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		ft_putstr_fd("fork failed\n", 2);
		exit(0);
	}
	if (cmd->pid == 0)
	{
		child_process(env, shell, cmd);
	}
	else
	{
		// parent_process(env, cmd);
	}
}

int	execution(t_list *env, t_minishell *shell, t_parse_cmd *cmd)
{
	bool pipe;
	t_parse_cmd *tmp;
	// int		old_in;

	(void)shell;
	if (!cmd->value)
		return (SUCCESS);
	tmp = cmd;
	pipe = tmp->next != NULL;
	while (tmp)
	{
		if (!pipe && is_a_builtin(tmp) == SUCCESS)
		{
			shell->exit_status = exec_builtin(env, tmp);
		}
		else if (tmp->next == NULL)
		{
			// le derneir pipe
		}
		else
		{
			// avant le dernier pipe
			do_fork(env, shell, tmp);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}