/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:20:54 by aditer            #+#    #+#             */
/*   Updated: 2024/01/05 10:03:04 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (nptr[i] && (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13)))
		i++;
	if (nptr[i] && nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] && nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9' && nptr[i])
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	return (res * sign);
}
