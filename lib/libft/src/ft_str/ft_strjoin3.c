/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 07:40:54 by aditer            #+#    #+#             */
/*   Updated: 2024/08/30 07:45:56 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	char	*dest;
	char	*ptr;
	int		total_len;

	if (!s1 || !s2 || !s3)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	dest = malloc(sizeof(char) * (total_len + 1));
	if (!dest)
		return (NULL);
	ptr = dest;
	while (*s1)
		*ptr++ = *s1++;
	while (*s2)
		*ptr++ = *s2++;
	while (*s3)
		*ptr++ = *s3++;
	*ptr = '\0';
	return (dest);
}
