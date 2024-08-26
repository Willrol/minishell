/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:06:36 by aditer            #+#    #+#             */
/*   Updated: 2024/08/26 16:46:24 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	isnotsp(char *line, int i)
{
	if (line[i] == '\'' || line[i] == '"' || line[i] == '$' || line[i] == '>'
		|| line[i] == '<' || line[i] == ' ' || line[i] == '|')
		return (1);
	return (0);
}

int	ft_mot(char *line, int i)
{
	int	j;

	j = 0;
	while (line[i] && isnotsp(line, i) == 0)
	{
		i++;
		j++;
	}
	return (j);
}

void	lexer(char *line)
{
	int		i;
	int		j;
	char	*truc;

	// t_list	*token;
	// t_token	*node_token;
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
		{
			i++;
			continue ;
		}
		if (isnotsp(line, i) == 0)
		{
			j = ft_mot(line, i);
			truc = ft_strtrim(ft_substr(line, i, j), " ");
			i += j;
			printf("%s\ni = %d\n", truc, i);
			free(truc);
		}
		else
			i++;
	}
}

//> >> < << $ | " " ' '