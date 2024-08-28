/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 07:40:54 by aditer            #+#    #+#             */
/*   Updated: 2024/08/28 14:06:21 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	int		i;
	int		j;
	int		k;
	char	*dest;

	i = 0;
	j = 0;
	k = 0;
	if (!s1 || !s2 || !s3)
		return (NULL);
	dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3))
			+ 1);
	if (!dest)
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dest[i] = s2[j];
		i++;
		j++;
	}
	while (s3[k])
	{
		dest[i] = s3[k];
		i++;
		k++;
	}
	dest[i] = 0;
	return (dest);
}
