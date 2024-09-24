/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:26:27 by aditer            #+#    #+#             */
/*   Updated: 2024/09/24 15:33:51 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remove_env(t_list **env, char **argv)
{
	t_list	*tmp;
	t_list	*prev;
	int		i;

	tmp = *env;
	prev = NULL;
	i = 1;
	while (argv[i])
	{
		while (tmp)
		{
			if (!ft_strncmp(((t_env *)tmp->content)->name, argv[i],
					ft_strlen(argv[i])))
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
