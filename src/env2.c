/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 08:11:12 by aditer            #+#    #+#             */
/*   Updated: 2024/10/07 13:32:29 by aditer           ###   ########.fr       */
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
		if (!ft_strcmp(((t_env *)tmp->content)->name, name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int remove_env(t_list **env, char *str)
{
	t_list *tmp;
	t_list *prev;

	if (!str || !*str)
		return (SUCCESS);
	tmp = *env;
	prev = NULL;

	while (tmp)
	{
		if (!ft_strcmp(((t_env *)tmp->content)->name, str))
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;

			free(((t_env *)tmp->content)->name);
			free(((t_env *)tmp->content)->content);
			free(tmp->content);
			free(tmp);
			break;
		}

		prev = tmp;
		tmp = tmp->next;
	}

	return (SUCCESS);
}