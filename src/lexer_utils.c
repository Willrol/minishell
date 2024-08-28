/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:02:32 by aditer            #+#    #+#             */
/*   Updated: 2024/08/28 14:04:44 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_token(t_list *token)
{
	t_list	*tmp;

	tmp = token;
	while (tmp)
	{
		printf("%s\n", ((t_token *)tmp->content)->value);
		printf("%d\n", ((t_token *)tmp->content)->type);
		tmp = tmp->next;
	}
}

void	free_token_list(t_list *token)
{
	t_list	*temp;
	t_token	*node_token;

	while (token)
	{
		temp = token;
		node_token = (t_token *)token->content;
		free(node_token->value);
		free(node_token);
		token = token->next;
		free(temp);
	}
}

int	isnotsp(char *line)
{
	if (line[0] == '\'' || line[0] == '"')
		return (3);
	if (line[0] == '$' || line[0] == '>' || line[0] == '<' || line[0] == '|'
		|| line[0] == ' ')
	{
		if ((line[0] == '<' && line[1] == '<') || (line[0] == '>'
				&& line[1] == '>'))
			return (2);
		return (1);
	}
	return (0);
}

int	ft_mot(char *line)
{
	int	j;

	j = 0;
	while (line[0] && isnotsp(line) == 0)
	{
		line++;
		j++;
	}
	return (j);
}

int	typval(char *value)
{
	if (value[0] == '\'')
		return (1);
	if (value[0] == '"')
		return (2);
	if (value[0] == '$')
		return (3);
	if (value[0] == '>')
	{
		if (value[1] == '>')
			return (4);
		return (5);
	}
	if (value[0] == '<')
	{
		if (value[1] == '<')
			return (6);
		return (7);
	}
	if (value[0] == '|')
		return (0);
	return (0);
}
