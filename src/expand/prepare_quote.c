/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:48:28 by aditer            #+#    #+#             */
/*   Updated: 2024/10/18 13:02:12 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cmd.h"

static void	check_minus_quote(t_parse_cmd *tmp, int i, int *j)
{
	char	quote;

	if (tmp->argv[i][*j] == '\'' || tmp->argv[i][*j] == '"')
	{
		quote = tmp->argv[i][*j];
		tmp->argv[i][*j] *= -1;
		while (tmp->argv[i][*j] && tmp->argv[i][*j] != quote)
			(*j)++;
		tmp->argv[i][*j] *= -1;
	}
}

void	minus_quote(t_parse_cmd *cmd)
{
	int			i;
	int			j;
	t_parse_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		i = -1;
		while (tmp->argv[++i])
		{
			j = -1;
			while (tmp->argv[i][++j])
			{
				check_minus_quote(tmp, i, &j);
			}
		}
		free(tmp->value);
		tmp->value = ft_strdup(tmp->argv[0]);
		tmp = tmp->next;
	}
}
