/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rderkaza <rderkaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:26:24 by aditer            #+#    #+#             */
/*   Updated: 2024/09/24 17:47:00 by rderkaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_equal(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

static void	free_tmps(char *tab1, char *tab2)
{
	free(tab1);
	free(tab2);
}

int	ft_export(t_list **env, char **argv)
{
	int		i;
	int		j;
	char	*tmp1;
	char	*tmp2;

	i = 1;
	while (argv[i])
	{
		j = count_equal(argv[i]);
		tmp1 = ft_substr(argv[i], 0, j);
		tmp2 = ft_substr(argv[i], j + 1, ft_strlen(argv[i]));
		if ((size_t)j == ft_strlen(argv[i]))
		{
			free_tmps(tmp1, tmp2);
			return ((FAILURE));
		}
		add_env(env, tmp1, tmp2);
		free_tmps(tmp1, tmp2);
		i++;
	}
	if (i == 1)
	{
		print_env(*env);
	}
	return (SUCCESS);
}

void	add_env(t_list **env, char *name, char *content)
{
	t_list *tmp;
	t_env *node_env;

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
		if (content[0] != '\0')
			node_env->content = ft_strdup(content);
		else
			node_env->content = ft_strdup("\"\"");
		tmp = ft_lstnew(node_env);
		if (!tmp)
			return ;
		ft_lstadd_back(env, tmp);
	}
}