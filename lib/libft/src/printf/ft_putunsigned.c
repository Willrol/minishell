/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:50:19 by aditer            #+#    #+#             */
/*   Updated: 2024/03/18 13:41:40 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_unsigned(unsigned int n)
{
	long	cpt;

	cpt = 0;
	if (n == 0)
		return (cpt + 1);
	while (n != 0)
	{
		n /= 10;
		cpt++;
	}
	return (cpt);
}

int	ft_putunsigned(unsigned int n)
{
	int				i;
	unsigned int	abs_n;

	i = len_unsigned(n);
	if (n < 0)
	{
		abs_n = -n;
		abs_n = ~abs_n + 1;
	}
	else
		abs_n = n;
	if (abs_n == 0)
	{
		ft_putchar('0');
		return (i);
	}
	else
	{
		if (n / 10 != 0)
			ft_putunsigned(n / 10);
		ft_putchar(n % 10 + '0');
		return (i);
	}
}
