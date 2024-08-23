/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:24:36 by aditer            #+#    #+#             */
/*   Updated: 2024/03/18 13:42:06 by aditer           ###   ########.fr       */
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

int	ft_putnbr(int n)
{
	int		i;
	long	nbr;

	nbr = n;
	i = len_nbr(nbr);
	if (nbr < 0)
	{
		ft_putchar('-');
		nbr *= -1;
	}
	if (nbr >= 10)
	{
		ft_putnbr(nbr / 10);
		ft_putchar(nbr % 10 + '0');
	}
	if (nbr < 10)
		ft_putchar(nbr + '0');
	return (i);
}
