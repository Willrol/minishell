/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 08:11:12 by aditer            #+#    #+#             */
/*   Updated: 2024/09/24 15:46:02 by aditer           ###   ########.fr       */
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
