/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 08:11:12 by aditer            #+#    #+#             */
/*   Updated: 2024/09/18 16:11:20 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*search_env(t_list *env, char *name)
{
	t_list	*tmp;

	if (!name || !*name)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(((t_env *)tmp->content)->name, name, ft_strlen(name)))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	add_env(t_list **env, char *name, char *content)
{
	t_list	*tmp;
	t_env	*node_env;

	tmp = search_env(*env, name);
	if (tmp)
	{
		free(((t_env *)tmp->content)->content);
		((t_env *)tmp->content)->content = ft_strdup(content);
	}
	else
	{
		node_env = ft_calloc(1, sizeof(t_env));
		if (!node_env)
			return ;
		node_env->name = ft_strdup(name);
		node_env->content = ft_strdup(content);
		tmp = ft_lstnew(node_env);
		if (!tmp)
			return ;
		ft_lstadd_back(env, tmp);
	}
}
