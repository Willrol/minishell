/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:40:44 by aditer            #+#    #+#             */
/*   Updated: 2024/10/22 10:22:55 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*make_path(t_list *env, t_minishell *shell)
{
	t_list	*path_node;
	char	*path;

	path = NULL;
	path_node = search_env(env, "PATH");
	if (!path_node && shell->path)
		path = ft_strdup(shell->path);
	else if (path_node)
		path = ft_strdup(((t_env *)path_node->content)->content);
	if (!path)
		return (NULL);
	return (path);
}

char	*exec(t_list *env, t_minishell *shell, t_parse_cmd *cmd)
{
	char	*path;
	char	**split_path;
	int		i;

	path = make_path(env, shell);
	if (!path)
		return (ft_strdup(cmd->value));
	i = -1;
	if (path)
	{
		split_path = ft_split(path, ':');
		while (split_path[++i])
		{
			if (path)
				free(path);
			path = ft_strjoin3(split_path[i], "/", cmd->value);
			shell->exit_status = test_path(path);
			if (shell->exit_status == SUCCESS)
				return (ft_free_tab(split_path), path);
		}
		ft_free_tab(split_path);
	}
	free(path);
	return (ft_strdup(cmd->value));
}

int	exec_command(t_list *env, t_minishell *shell, t_parse_cmd *cmd)
{
	char	*path;
	char	**env_tab;

	if (is_dir(cmd->value))
	{
		error_exec(cmd->value, IS_DIR);
		return (IS_DIR);
	}
	path = exec(env, shell, cmd);
	env_tab = get_env_tab(env);
	shell->exit_status = test_path(path);
	if (shell->exit_status != SUCCESS)
	{
		error_exec(cmd->value, shell->exit_status);
		free(path);
		return (ft_free_tab(env_tab), shell->exit_status);
	}
	execve(path, cmd->argv, env_tab);
	shell->exit_status = CMD_NFOUND;
	error_exec(cmd->value, shell->exit_status);
	free(path);
	ft_free_tab(env_tab);
	return (shell->exit_status);
}

int	do_command(t_list *env, t_minishell *shell, t_parse_cmd *cmd)
{
	int	ret;

	if (is_a_builtin(cmd) == SUCCESS)
		ret = exec_builtin(shell, cmd);
	else
		ret = exec_command(env, shell, cmd);
	return (ret);
}
