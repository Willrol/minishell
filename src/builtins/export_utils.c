/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:20:36 by aditer            #+#    #+#             */
/*   Updated: 2024/10/22 10:25:15 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_name(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[0]) == 0)
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		free(str);
		return (FAILURE);
	}
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0)
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			free(str);
			return (FAILURE);
		}
		i++;
	}
	return (0);
}

int	count_equal(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] == '=')
			return (i);
		i++;
	}
	return (i);
}
