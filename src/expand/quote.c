/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:16:41 by aditer            #+#    #+#             */
/*   Updated: 2024/10/17 13:38:25 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cmd.h"

char	*remove_char(char *str, int index)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (str[i])
	{
		if (i != index)
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = 0;
	free(str);
	return (new_str);
}

int	removing(char **argv, int i, int j)
{
	char	quote;

	while (argv[i][j])
	{
		if (argv[i][j] == '\'' || argv[i][j] == '"')
		{
			quote = argv[i][j];
			argv[i] = remove_char(argv[i], j);
			if (!argv[i])
				return (FAILURE);
			while (argv[i][j] && argv[i][j] != quote)
				j++;
			if (argv[i][j] == quote)
			{
				argv[i] = remove_char(argv[i], j);
				if (!argv[i])
					return (FAILURE);
				continue ;
			}
		}
		j++;
	}
	return (SUCCESS);
}

int	remove_quote(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (removing(argv, i, 0) == FAILURE)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	remove_quote_redir(char **file_name)
{
	int		i;
	char	quote;

	i = 0;
	while ((*file_name)[i])
	{
		if ((*file_name)[i] == '\'' || (*file_name)[i] == '"')
		{
			quote = (*file_name)[i];
			(*file_name) = remove_char((*file_name), i);
			if (!(*file_name))
				return (FAILURE);
			while ((*file_name)[i] && (*file_name)[i] != quote)
				i++;
			if ((*file_name)[i] == quote)
			{
				(*file_name) = remove_char((*file_name), i);
				if (!(*file_name))
					return (FAILURE);
				continue ;
			}
		}
		i++;
	}
	return (SUCCESS);
}
