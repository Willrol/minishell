/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:16:41 by aditer            #+#    #+#             */
/*   Updated: 2024/09/18 16:29:04 by aditer           ###   ########.fr       */
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
		return (NULL);
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

void	remove_quote(char **argv)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == '\'' || argv[i][j] == '"')
			{
				quote = argv[i][j];
				argv[i] = remove_char(argv[i], j);
				while (argv[i][j] && argv[i][j] != quote)
					j++;
				if (argv[i][j] == quote)
					argv[i] = remove_char(argv[i], j);
			}
			j++;
		}
		i++;
	}
}
