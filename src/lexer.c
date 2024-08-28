/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:06:36 by aditer            #+#    #+#             */
/*   Updated: 2024/08/28 14:02:25 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	wordintake(char *line, t_list **token, int *flag)
{
	int		j;
	t_token	*node_token;

	j = ft_mot(line);
	node_token = calloc(1, sizeof(t_token));
	if (!node_token)
		return (FAILURE);
	node_token->value = ft_substr(line, 0, j);
	node_token->type = 0;
	ft_lstadd_back(token, ft_lstnew(node_token));
	*flag = 0;
	return (j);
}

int	process_double_quote(const char *line, t_list **token)
{
	int		j;
	t_token	*node_token;

	j = 1;
	while (line[j] && line[j] != line[0])
		j++;
	if (!line[j])
	{
		ft_putstr_fd("Error: Unclosed double quote.\n", 2);
		free_token_list(*token);
		return (FAILURE);
	}
	node_token = calloc(1, sizeof(t_token));
	if (!node_token)
		return (FAILURE);
	node_token->value = ft_substr(line, 0, j + 1);
	node_token->type = typval(node_token->value);
	ft_lstadd_back(token, ft_lstnew(node_token));
	return (j + 1);
}

int	process_token(char *line, t_list **token, int *flag)
{
	t_token	*node_token;
	int		tmptype;

	tmptype = 0;
	node_token = calloc(1, sizeof(t_token));
	if (!node_token)
	{
		free_token_list(*token);
		return (FAILURE);
	}
	node_token->value = ft_substr(line, 0, isnotsp(line));
	if (*flag == 1 && (tmptype == typval(node_token->value) || tmptype > 3))
	{
		printf("error\n");
		free(node_token->value);
		free(node_token);
		free_token_list(*token);
		return (FAILURE);
	}
	node_token->type = typval(node_token->value);
	tmptype = node_token->type;
	ft_lstadd_back(token, ft_lstnew(node_token));
	*flag = 1;
	return (isnotsp(line));
}

void	lexer(char *line)
{
	int		err;
	int		flag;
	t_list	*token;

	flag = 0;
	token = NULL;
	while (line[0])
	{
		if (line[0] == ' ')
		{
			line++;
			continue ;
		}
		if (isnotsp(line) == 0)
			err = E(line, &token, &flag);
		else if (isnotsp(line) == 3)
			err = process_double_quote(line, &token);
		else
			err = process_token(line, &token, &flag);
		line += err;
		if (err == FAILURE)
			return ;
	}
	print_token(token);
	free_token_list(token);
}
