/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 10:54:04 by aditer            #+#    #+#             */
/*   Updated: 2024/01/05 10:06:08 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_char(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	char	*dest;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1);
	k = 0;
	while (s1[i] && find_char(s1[i], set))
		i++;
	while (i < j && find_char(s1[j - 1], set))
		j--;
	dest = malloc(sizeof(char) * j - i + 1);
	if (!dest)
		return (NULL);
	while (i < j)
	{
		dest[k] = s1[i];
		k++;
		i++;
	}
	dest[k] = 0;
	return (dest);
}
