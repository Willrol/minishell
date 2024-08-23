/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:01:41 by aditer            #+#    #+#             */
/*   Updated: 2024/03/18 13:42:21 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	format(char c, va_list list)
{
	int	i;

	if (c == 'c')
		i = ft_putchar(va_arg(list, int));
	if (c == 's')
		i = ft_putstr(va_arg(list, char *));
	if (c == 'p')
		i = ft_putptr(va_arg(list, void *));
	if (c == 'd' || c == 'i')
		i = ft_putnbr(va_arg(list, unsigned int));
	if (c == 'u')
		i = ft_putunsigned(va_arg(list, unsigned int));
	if (c == 'x' || c == 'X')
		i = ft_puthex(va_arg(list, int), c);
	if (c == '%')
		i = ft_putchar('%');
	return (i - 1);
}

int	ft_printf(const char *t, ...)
{
	int		i;
	int		j;
	va_list	list;

	i = 0;
	j = 0;
	if (t == NULL)
		return (-1);
	va_start(list, t);
	while (t[i])
	{
		if (t[i] == '%')
		{
			j += format(t[i + 1], list);
			i++;
		}
		else
			ft_putchar(t[i]);
		i++;
		j++;
	}
	va_end(list);
	return (j);
}
