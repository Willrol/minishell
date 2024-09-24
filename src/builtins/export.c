/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:26:24 by aditer            #+#    #+#             */
/*   Updated: 2024/09/24 15:46:11 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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