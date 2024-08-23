/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:44:26 by aditer            #+#    #+#             */
/*   Updated: 2023/11/20 11:36:28 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dest_tmp;
	char	*src_tmp;
	size_t	i;

	dest_tmp = (char *)dest;
	src_tmp = (char *)src;
	i = 0;
	if (!dest && !src)
		return (NULL);
	if (dest_tmp > src_tmp)
	{
		while (n-- > 0)
			dest_tmp[n] = src_tmp[n];
	}
	else
	{
		while (i < n)
		{
			dest_tmp[i] = src_tmp[i];
			i++;
		}
	}
	return (dest_tmp);
}
