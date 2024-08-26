/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:06:36 by aditer            #+#    #+#             */
/*   Updated: 2024/08/26 15:21:25 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	lexer(char *line)
{
	int i;

	i = 0;
	t_list *token;
	t_token *node_token;
	while(line[i])
	{
		node_token = ft_calloc(1, sizeof(t_token));
		if (!node_token)
			return ;
		

	}
	
}
