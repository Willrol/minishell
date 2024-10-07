/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:26:27 by aditer            #+#    #+#             */
/*   Updated: 2024/10/07 13:36:06 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(t_list **env, char **argv)
{
	t_list	*tmp;
	t_list	*prev;
	int		i;

	i = 1;
	while (argv[i])
	{
		tmp = *env;
		prev = NULL;
		while (tmp)
		{
			if (!ft_strcmp(((t_env *)tmp->content)->name, argv[i]))
			{
				if (prev)
					prev->next = tmp->next;
				else
					*env = tmp->next;
				free(((t_env *)tmp->content)->name);
				free(((t_env *)tmp->content)->content);
				free(tmp->content);
				free(tmp);
				break ;
			}
			prev = tmp;
			tmp = tmp->next;
		}
		i++;
	}
	return (SUCCESS);
}
