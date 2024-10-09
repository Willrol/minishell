/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:05:48 by aditer            #+#    #+#             */
/*   Updated: 2024/10/08 17:06:11 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cmd.h"

void	count_word_utils(char *str, int *count, int *i)
{
	if (str[*i] == ' ')
	{
		(*count)++;
		while (str[*i] && str[*i] == ' ')
			(*i)++;
	}
	else
		(*i)++;
}

int	count_word(char *str)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 1;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			if (str[i++] == quote)
				continue ;
		}
		else
			count_word_utils(str, &count, &i);
	}
	return (count);
}

static int	do_split(char ***argv, char ***new_argv, int i, int nb)
{
	int		j;
	int		k;
	char	**split;

	j = 0;
	while (j != i)
	{
		(*new_argv)[j] = ft_strdup((*argv)[j]);
		if (!(*new_argv)[j])
		{
			ft_free_tab((*new_argv));
			return (FAILURE);
		}
		j++;
	}
	split = ft_split((*argv)[i], ' ');
	if (!split)
		return (FAILURE);
	k = 0;
	while (split[k])
	{
		(*new_argv)[j] = ft_strdup(split[k]);
		if (!(*new_argv)[j])
		{
			ft_free_tab(split);
			ft_free_tab((*new_argv));
			return (FAILURE);
		}
		j++;
		k++;
	}
	ft_free_tab(split);
	while ((*argv)[j - nb + 1])
	{
		(*new_argv)[j] = ft_strdup((*argv)[j - nb + 1]);
		if (!(*new_argv)[j])
		{
			ft_free_tab((*new_argv));
			return (FAILURE);
		}
		j++;
	}
	return (SUCCESS);
}

int	split_expand(int *argc, char ***argv)
{
	int		i;
	int		nb;
	char	**new_argv;

	i = 0;
	new_argv = NULL;
	while ((*argv)[i])
	{
		nb = count_word((*argv)[i]);
		(*argc) += nb - 1;
		if (nb > 1)
		{
			new_argv = ft_calloc((*argc) + 1, sizeof(char *));
			if (!new_argv)
				return (FAILURE);
			if (do_split(argv, &new_argv, i, nb) == FAILURE)
			{
				ft_free_tab((new_argv));
				return (FAILURE);
			}
		}
		i++;
	}
	if (new_argv != NULL)
	{
		ft_free_tab((*argv));
		(*argv) = new_argv;
	}
	return (SUCCESS);
}
