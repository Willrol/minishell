/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rderkaza <rderkaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:40:44 by aditer            #+#    #+#             */
/*   Updated: 2024/10/14 13:23:34 by rderkaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*make_path(t_list *env, t_minishell *shell)
{
	t_list	*path_node;
	char	*path;

	path_node = search_env(env, "PATH");
	if (!path_node)
		path = ft_strdup(shell->path);
	else
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
		return (NULL);
	i = -1;
	if (path)
	{
		split_path = ft_split(path, ':');
		while (split_path[++i])
		{
			if (path)
				free(path);
			path = ft_strjoin3(split_path[i], "/", cmd->value);
			if (access(path, F_OK | X_OK) == 0)
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

	path = exec(env, shell, cmd);
	env_tab = get_env_tab(env);
	if (execve(path, cmd->argv, env_tab) == FAILURE)
	{
		error_exec(cmd->value);
		free(path);
		ft_free_tab(env_tab);
		return (127);
	}
	return (SUCCESS);
}

int	do_command(t_list *env, t_minishell *shell, t_parse_cmd *cmd)
{
	int	ret;

	if (is_a_builtin(cmd) == SUCCESS)
		ret = exec_builtin(env, shell, cmd);
	else
		ret = exec_command(env, shell, cmd);
	return (ret);
}
