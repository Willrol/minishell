/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:06:36 by aditer            #+#    #+#             */
/*   Updated: 2024/10/09 13:11:06 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_closed_quotes(char *value)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = -1;
	single_quote = 0;
	double_quote = 0;
	while (value[++i])
	{
		if (value[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		if (value[i] == '"' && !single_quote)
			double_quote = !double_quote;
	}
	if (single_quote && !double_quote)
	{
		ft_putstr_fd("Error: Unclosed single quote.\n", 2);
		return (FAILURE);
	}
	else if (double_quote && !single_quote)
	{
		ft_putstr_fd("Error: Unclosed double quote.\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	wordintake(char *line, t_list **token, int *flag)
{
	int		j;
	t_token	*node_token;
	t_list	*new_node;

	j = ft_mot(line);
	node_token = ft_calloc(1, sizeof(t_token));
	if (!node_token)
		return (FAILURE);
	node_token->value = ft_substr(line, 0, j);
	if (!node_token->value)
	{
		free(node_token);
		return (FAILURE);
	}
	node_token->type = 0;
	new_node = ft_lstnew(node_token);
	if (!new_node)
	{
		free(node_token->value);
		free(node_token);
		return (FAILURE);
	}
	ft_lstadd_back(token, new_node);
	*flag = 0;
	return (j);
}

t_valuetype	process_token(char *line, t_list **token, int *flag,
		t_valuetype *tmptype)
{
	t_token	*node_token;

	node_token = ft_calloc(1, sizeof(t_token));
	if (!node_token)
	{
		free_token_list(*token);
		return (FAILURE);
	}
	node_token->value = ft_substr(line, 0, isnotsp(line));
	if (!node_token->value)
	{
		free(node_token);
		free_token_list(*token);
		return (FAILURE);
	}
	if ((*flag == 1 && (*tmptype == typval(node_token->value) || *tmptype > 4))
		|| !line[1] || (!line[2] && line[1] == line[0]))
	{
		lexer_error(token, node_token);
		return (FAILURE);
	}
	node_token->type = typval(node_token->value);
	*tmptype = node_token->type;
	ft_lstadd_back(token, ft_lstnew(node_token));
	*flag = 1;
	return (isnotsp(line));
}

void	skip_spaces(char **line)
{
	while (**line == ' ')
		(*line)++;
}

t_list	*lexer(char *line)
{
	int			err;
	int			flag;
	t_list		*token;
	t_valuetype	tmptype;
	char		*tmp;

	flag = 0;
	token = NULL;
	tmp = line;
	if (tmp[0] == '|')
		return (ft_putstr_fd("Error: Syntax error near unexpected token '|'\n",
				2), NULL);
	if (check_closed_quotes(tmp) == FAILURE)
		return (NULL);
	while (tmp[0])
	{
		skip_spaces(&tmp);
		if (isnotsp(tmp) == 0 || isnotsp(tmp) == 3)
			err = wordintake(tmp, &token, &flag);
		else
			err = process_token(tmp, &token, &flag, &tmptype);
		if (err == FAILURE)
			return (NULL);
		tmp += err;
	}
	return (token);
}
