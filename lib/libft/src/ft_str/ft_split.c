/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:57:13 by aditer            #+#    #+#             */
/*   Updated: 2024/03/18 14:21:11 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_split(char **split_result)
{
	int	i;

	i = 0;
	if (split_result)
	{
		while (split_result[i] != NULL)
		{
			free(split_result[i]);
			i++;
		}
		free(split_result);
	}
}

int	count_words(char const *s, char c)
{
	int	i;
	int	j;
	int	cpt;

	i = 0;
	j = 0;
	cpt = 0;
	while (s[i])
	{
		if (s[i] != c && j == 0)
		{
			j = 1;
			cpt++;
		}
		if (s[i] == c)
			j = 0;
		i++;
	}
	return (cpt);
}

static char	*create_words(char const *s, int start, int end)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = s[start];
		i++;
		start++;
	}
	word[i] = 0;
	return (word);
}

static char	**fill_tab(char const *s, char c, char **dest)
{
	size_t	i;
	size_t	j;
	int		k;

	i = 0;
	j = 0;
	k = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && k < 0)
			k = i;
		else if ((s[i] == c || i == ft_strlen(s)) && k >= 0)
		{
			dest[j] = create_words(s, k, i);
			if (dest == NULL)
				free_split(dest);
			j++;
			k = -1;
		}
		i++;
	}
	dest[j] = 0;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;

	if (!s)
		return (NULL);
	dest = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!dest)
		return (NULL);
	dest = fill_tab(s, c, dest);
	return (dest);
}
