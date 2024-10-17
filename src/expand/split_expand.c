/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:05:48 by aditer            #+#    #+#             */
/*   Updated: 2024/10/17 13:56:03 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cmd.h"

static int	copy_elements_up_to_index(char ***argv, char ***new_argv, int *i,
		int *j)
{
	while (*j != *i)
	{
		(*new_argv)[*j] = ft_strdup((*argv)[*j]);
		if (!(*new_argv)[*j])
		{
			ft_free_tab((*new_argv));
			return (FAILURE);
		}
		(*j)++;
	}
	return (SUCCESS);
}

static int	split_and_copy_elements(char ***argv, char ***new_argv, int *i,
		int *j)
{
	char	**split;
	int		k;

	split = ft_split((*argv)[*i], ' ');
	if (!split)
		return (FAILURE);
	k = 0;
	while (split[k])
	{
		(*new_argv)[*j] = ft_strdup(split[k]);
		if (!(*new_argv)[*j])
		{
			ft_free_tab(split);
			ft_free_tab((*new_argv));
			return (FAILURE);
		}
		(*j)++;
		k++;
	}
	ft_free_tab(split);
	return (SUCCESS);
}

static int	copy_remaining_elements(char ***argv, char ***new_argv, int *j,
		int nb)
{
	while ((*argv)[*j - nb + 1])
	{
		(*new_argv)[*j] = ft_strdup((*argv)[*j - nb + 1]);
		if (!(*new_argv)[*j])
		{
			ft_free_tab((*new_argv));
			return (FAILURE);
		}
		(*j)++;
	}
	return (SUCCESS);
}

static int	do_split(char ***argv, char ***new_argv, int *i, int nb)
{
	int	j;

	j = 0;
	if (copy_elements_up_to_index(argv, new_argv, i, &j) == FAILURE)
		return (FAILURE);
	if (split_and_copy_elements(argv, new_argv, i, &j) == FAILURE)
		return (FAILURE);
	if (copy_remaining_elements(argv, new_argv, &j, nb) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	split_expand(int *argc, char ***argv)
{
	int		i;
	int		nb;
	char	**new_argv;

	i = -1;
	new_argv = NULL;
	while ((*argv)[++i])
	{
		nb = count_word((*argv)[i]);
		(*argc) += nb - 1;
		if (nb > 1)
		{
			new_argv = ft_calloc((*argc) + 1, sizeof(char *));
			if (!new_argv)
				return (FAILURE);
			if (do_split(argv, &new_argv, &i, nb) == FAILURE)
			{
				ft_free_tab((new_argv));
				return (FAILURE);
			}
		}
	}
	check_argv(argv, new_argv);
	trim_argv(argv);
	return (SUCCESS);
}
