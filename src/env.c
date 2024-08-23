/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:00:59 by aditer            #+#    #+#             */
/*   Updated: 2024/08/23 13:32:03 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*init_env(char **envp)
{
	t_list	*env;
	t_list	*tmp;
	t_env	*node_env;
	int		i;
	int		limit;

	i = -1;
	env = NULL;
	while (envp[++i])
	{
		node_env = ft_calloc(1, sizeof(t_env));
		if (!node_env)
			return (NULL);
		limit = ft_strchr(envp[i], '=') - envp[i] + 1;
		node_env->name = ft_calloc(limit, sizeof(char));
		if (!node_env->name)
			return (NULL);
		ft_strlcpy(node_env->name, envp[i], limit);
		node_env->content = limit + envp[i] + 1;
		tmp = ft_lstnew(node_env);
		if (!tmp)
			return (NULL);
		ft_lstadd_back(&env, tmp);
	}
	return (env);
}

void	print_env(t_list *env)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		printf("%s=%s\n", ((t_env *)tmp->content)->name,
			((t_env *)tmp->content)->content);
		tmp = tmp->next;
	}
}

void	free_env(t_list *env)
{
	t_list	*tmp;

	tmp = env;
	while (env)
	{
		tmp = env->next;
		free(((t_env *)env->content)->name);
		free(env->content);
		free(env);
		env = tmp;
	}
}

char	**get_env_tab(t_list *env)
{
	int		i;
	int		size;
	t_list	*tmp;
	char	**tab_env;

	i = 0;
	size = ft_lstsize(env);
	tmp = env;
	tab_env = ft_calloc(size + 1, sizeof(char *));
	if (!tab_env)
		return (NULL);
	while (tmp)
	{
		tab_env[i] = ft_strjoin3(((t_env *)tmp->content)->name, "=",
				((t_env *)tmp->content)->content);
		if (!tab_env)
		{
			ft_free_tab(tab_env);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	tab_env[i] = NULL;
	return (tab_env);
}

