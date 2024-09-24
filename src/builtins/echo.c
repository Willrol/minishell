/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:26:14 by aditer            #+#    #+#             */
/*   Updated: 2024/09/24 18:32:26 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_n_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (false);
	i++;
	while (str[i] == 'n')
		i++;
	if (str[i] == '\0')
		return (true);
	return (false);
}

int	echo(int argc, char **argv)
{
	int		n_flag;
	char	**move;

	if (argc > 1)
	{
		move = argv + 1;
		n_flag = 0;
		if (is_n_flag(*move))
		{
			n_flag = 1;
			++move;
		}
		while (*move)
		{
			ft_putstr_fd(*move, 1);
			if (*(move + 1))
				ft_putstr_fd(" ", 1);
			++move;
		}
		if (!n_flag)
			ft_putstr_fd("\n", 1);
	}
	return (SUCCESS);
}
