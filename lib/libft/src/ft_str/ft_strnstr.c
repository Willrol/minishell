/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:16:47 by aditer            #+#    #+#             */
/*   Updated: 2023/11/20 14:25:19 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		j;
	char	*res;

	i = 0;
	if (little[i] == 0)
		return ((char *)big);
	if (len == 0)
		return (NULL);
	while (big[i] && i < len)
	{
		if (big[i] == little[0])
		{
			res = (char *)big + i;
			j = 0;
			while (big[i + j] == little[j] && i + j < len)
			{
				if (little[j + 1] == 0)
					return (res);
				j++;
			}
		}
	i++;
	}
	return (NULL);
}
