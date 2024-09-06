/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:26:27 by aditer            #+#    #+#             */
/*   Updated: 2024/09/05 15:02:18 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env(t_list **env, char *name)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strncmp(((t_env *)tmp->content)->name, name, ft_strlen(name)))
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			free(((t_env *)tmp->content)->name);
			free(((t_env *)tmp->content)->content);
			free(tmp->content);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
