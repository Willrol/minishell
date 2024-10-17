/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:26:27 by aditer            #+#    #+#             */
/*   Updated: 2024/10/17 08:17:18 by aditer           ###   ########.fr       */
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

void	free_shell_path(t_minishell *shell, char *name)
{
	if (shell->path && !ft_strcmp("PATH", name))
	{
		free(shell->path);
		shell->path = NULL;
	}
}

void	remove_env_var(t_list **env, char *name)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strcmp(((t_env *)tmp->content)->name, name))
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

int	unset(t_list **env, t_minishell *shell, char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		free_shell_path(shell, argv[i]);
		remove_env_var(env, argv[i]);
	}
	return (SUCCESS);
}
