/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:26:24 by aditer            #+#    #+#             */
/*   Updated: 2024/10/17 13:20:44 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*add_node(char *name, char *content)
{
	t_env	*node_env;

	node_env = ft_calloc(1, sizeof(t_env));
	if (!node_env)
		return (NULL);
	node_env->name = ft_strdup(name);
	if (content[0] != '\0')
		node_env->content = ft_strdup(content);
	else
		node_env->content = ft_strdup("");
	if (!node_env->name || !node_env->content)
		return (NULL);
	return (node_env);
}

int	add_env(t_list **env, char *name, char *content)
{
	t_list	*tmp;
	t_env	*node_env;

	tmp = search_env(*env, name);
	if (tmp)
	{
		free(((t_env *)tmp->content)->content);
		((t_env *)tmp->content)->content = ft_strdup(content);
		if (!((t_env *)tmp->content)->content)
			return (FAILURE);
	}
	else
	{
		node_env = add_node(name, content);
		if (!node_env)
			return (FAILURE);
		tmp = ft_lstnew(node_env);
		if (!tmp)
		{
			free(node_env);
			return (FAILURE);
		}
		ft_lstadd_back(env, tmp);
	}
	return (SUCCESS);
}

int	process_argument(t_list **env, t_minishell *shell, char *arg)
{
	int		j;
	char	*tmp1;
	char	*tmp2;

	j = count_equal(arg);
	tmp1 = ft_substr(arg, 0, j);
	if (!tmp1)
		error_malloc(shell, *env);
	if (valid_name(tmp1) == FAILURE)
		return (FAILURE);
	tmp2 = ft_substr(arg, j + 1, ft_strlen(arg));
	if (!tmp2)
	{
		free(tmp1);
		error_malloc(shell, *env);
	}
	if ((size_t)j == ft_strlen(arg))
	{
		free_tmps(tmp1, tmp2);
		return (FAILURE);
	}
	add_env(env, tmp1, tmp2);
	free_tmps(tmp1, tmp2);
	return (SUCCESS);
}

int	ft_export(t_list **env, t_minishell *shell, char **argv)
{
	int	i;
	int	result;

	i = 1;
	while (argv[i])
	{
		result = process_argument(env, shell, argv[i]);
		if (result == FAILURE)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
