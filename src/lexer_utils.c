/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:02:32 by aditer            #+#    #+#             */
/*   Updated: 2024/09/23 13:38:14 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (line[0] == '>' || line[0] == '<' || line[0] == '|')
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
	int		j;
	char	quote;

	j = 0;
	while (line[0] && isnotsp(line) == 0 && line[0] != ' ')
	{
		line++;
		j++;
	}
	if (line[0] == '"' || line[0] == '\'')
	{
		quote = line[0];
		line++;
		j++;
		while (line[0] && line[0] != quote)
		{
			line++;
			j++;
		}
		line++;
		j++;
		j += ft_mot(line);
	}
	return (j);
}

t_valuetype	typval(char *value)
{
	if (value[0] == '\'')
		return (SINGLE_QUOTE);
	else if (value[0] == '"')
		return (DOUBLE_QUOTE);
	else if (value[0] == '$')
		return (DOLLAR);
	else if (value[0] == '>')
	{
		if (value[1] == '>')
			return (APPEND);
		return (OUT);
	}
	else if (value[0] == '<')
	{
		if (value[1] == '<')
			return (HERE_DOC);
		return (IN);
	}
	else if (value[0] == '|')
		return (PIPE);
	else
		return (0);
}

void	lexer_error(t_list **token, t_token *node_token)
{
	ft_putstr_fd("Error: Syntax error near unexpected token ", 2);
	ft_putchar_fd('\'', 2);
	ft_putstr_fd(node_token->value, 2);
	ft_putstr_fd("\'\n", 2);
	free(node_token->value);
	free(node_token);
	free_token_list(*token);
}
