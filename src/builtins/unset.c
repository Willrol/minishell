/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:26:27 by aditer            #+#    #+#             */
/*   Updated: 2024/10/16 15:01:57 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_temp(t_list *tmp)
{
	free(((t_env *)tmp->content)->name);
	free(((t_env *)tmp->content)->content);
	free(tmp->content);
	free(tmp);
}

int	unset(t_list **env, char **argv)
{
	t_list	*tmp;
	t_list	*prev;
	int		i;

	i = 0;
	while (argv[++i])
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
				free_temp(tmp);
				break ;
			}
			prev = tmp;
			tmp = tmp->next;
		}
	}
	return (SUCCESS);
}
