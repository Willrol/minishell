/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:02:59 by aditer            #+#    #+#             */
/*   Updated: 2024/03/18 13:42:12 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_hex(unsigned int n)
{
	long	cpt;

	cpt = 0;
	if (n == 0)
		return (cpt + 1);
	while (n != 0)
	{
		n /= 16;
		cpt++;
	}
	return (cpt);
}

int	ft_puthex(unsigned int n, char format)
{
	int		rem;
	int		i;
	char	hex;
	long	nbr;

	nbr = n;
	i = len_hex(nbr);
	rem = nbr % 16;
	if (nbr >= 16)
		ft_puthex(nbr / 16, format);
	if (rem < 10)
		hex = rem + '0';
	else
	{
		if (format == 'X')
			hex = rem + 'A' - 10;
		if (format == 'x')
			hex = rem + 'a' - 10;
	}
	ft_putchar(hex);
	return (i);
}
