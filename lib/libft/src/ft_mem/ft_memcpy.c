/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:30:53 by aditer            #+#    #+#             */
/*   Updated: 2024/05/16 13:10:34 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	while (n >= sizeof(size_t))
	{
		*(size_t *)d = *(size_t *)s;
		d += sizeof(size_t);
		s += sizeof(size_t);
		n -= sizeof(size_t);
	}
	while (n > 0)
	{
		*d++ = *s++;
		n--;
	}
	return (dest);
}
