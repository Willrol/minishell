/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:04:30 by aditer            #+#    #+#             */
/*   Updated: 2024/03/18 13:42:04 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printhex(unsigned long long num)
{
	int					cpt;
	char				hex;
	unsigned long long	tmp;

	cpt = 0;
	if (num / 16 != 0)
		cpt += printhex(num / 16);
	tmp = num % 16;
	if (tmp < 10)
		hex = tmp + '0';
	else
		hex = tmp - 10 + 'a';
	ft_putchar(hex);
	cpt++;
	return (cpt);
}

int	ft_putptr(void *ptr)
{
	unsigned long long	res;

	res = (unsigned long long)ptr;
	if (res == 0)
	{
		ft_putstr("(nil)");
		return (5);
	}
	ft_putchar('0');
	ft_putchar('x');
	return (printhex(res) + 2);
}
