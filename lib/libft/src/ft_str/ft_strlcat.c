/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:46:05 by aditer            #+#    #+#             */
/*   Updated: 2023/11/20 11:37:46 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_src;
	size_t	len_dst;
	size_t	i;

	i = 0;
	if (size == 0)
	{
		if (src)
			return (ft_strlen(src));
		return (0);
	}
	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	while (i + len_dst < size - 1 && src[i])
	{
		dst[i + len_dst] = src[i];
		i++;
	}
	if (size <= len_dst)
		return (size + len_src);
	dst[i + len_dst] = 0;
	return (len_src + len_dst);
}
