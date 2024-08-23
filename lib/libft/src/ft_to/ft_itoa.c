/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 09:49:58 by aditer            #+#    #+#             */
/*   Updated: 2024/01/05 10:03:13 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_nbr(int n)
{
	long	cpt;
	long	i;

	cpt = 1;
	i = n;
	if (i < 0)
	{
		i *= -1;
		cpt++;
	}
	while (i > 9)
	{
		i /= 10;
		cpt++;
	}
	return (cpt);
}

char	*ft_itoa(int n)
{
	int			cpt;
	long		tmp;
	char		*dest;

	tmp = n;
	cpt = len_nbr(n);
	dest = malloc(sizeof(char) * (cpt + 1));
	if (!dest)
		return (NULL);
	if (tmp < 0)
	{
		dest[0] = '-';
		tmp *= -1;
	}
	dest[cpt] = '\0';
	cpt--;
	while ((cpt > 1 && n < 0) || (cpt > 0 && n > 0))
	{
		dest[cpt] = (tmp % 10) + '0';
		tmp /= 10;
		cpt--;
	}
	dest[cpt] = tmp + '0';
	return (dest);
}
