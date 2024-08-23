/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:00:48 by aditer            #+#    #+#             */
/*   Updated: 2024/01/05 10:04:32 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const	void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_tmp;
	unsigned char	*s2_tmp;

	s1_tmp = (unsigned char *)s1;
	s2_tmp = (unsigned char *)s2;
	while (n > 0)
	{
		if (*s1_tmp != *s2_tmp)
			return (*s1_tmp - *s2_tmp);
		s1_tmp++;
		s2_tmp++;
		n--;
	}
	return (0);
}
