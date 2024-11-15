/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:18:40 by aditer            #+#    #+#             */
/*   Updated: 2024/10/22 13:58:52 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cmd.h"

int	cpt_word(t_list *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (((t_token *)token->content)->type == APPEND
			|| ((t_token *)token->content)->type == OUT
			|| ((t_token *)token->content)->type == HERE_DOC
			|| ((t_token *)token->content)->type == IN)
			token = token->next;
		else if (((t_token *)token->content)->type == WORD)
			count++;
		else if (((t_token *)token->content)->type == PIPE)
			break ;
		token = token->next;
	}
	return (count);
}

int	next_cmd(t_list *t_tmp, t_parse_cmd *cmd_tmp)
{
	if (t_tmp && ((t_token *)t_tmp->content)->type == PIPE && to_next_cmd(t_tmp,
			cmd_tmp) == FAILURE)
		return (FAILURE);
	if (cmd_tmp->argc > 0)
		cmd_tmp->value = ft_strdup(cmd_tmp->argv[0]);
	return (SUCCESS);
}

int	take_cmd(t_list *t_tmp, t_parse_cmd *cmd_tmp)
{
	int	i;

	i = 0;
	cmd_tmp->argc = cpt_word(t_tmp);
	cmd_tmp->argv = ft_calloc(cmd_tmp->argc + 1, sizeof(char *));
	if (!cmd_tmp->argv)
		return (FAILURE);
	cmd_tmp->pid = -1;
	while (t_tmp && ((t_token *)t_tmp->content)->type != PIPE)
	{
		if (sign_chk(((t_token *)t_tmp->content)->type) == 1)
			t_tmp = t_tmp->next;
		else if (((t_token *)t_tmp->content)->type == WORD)
		{
			cmd_tmp->argv[i] = ft_strdup(((t_token *)t_tmp->content)->value);
			if (!cmd_tmp->argv[i])
				return (FAILURE);
			i++;
		}
		cmd_tmp->argv[i] = NULL;
		t_tmp = t_tmp->next;
	}
	return (next_cmd(t_tmp, cmd_tmp));
}

int	take_redirection(t_list *t_tmp, t_parse_cmd *cmd_tmp)
{
	t_redirection	*redir;

	while (t_tmp && ((t_token *)t_tmp->content)->type != PIPE)
	{
		if (sign_chk(((t_token *)t_tmp->content)->type) == 1)
		{
			redir = ft_calloc(1, sizeof(t_redirection));
			if (!redir)
				return (FAILURE);
			redir->type = ((t_token *)t_tmp->content)->type;
			t_tmp = t_tmp->next;
			redir->file_name = ft_strdup(((t_token *)t_tmp->content)->value);
			if (!redir->file_name)
				return (free(redir), FAILURE);
			redir->next = NULL;
			append_redir(redir, cmd_tmp);
		}
		t_tmp = t_tmp->next;
	}
	if (t_tmp && ((t_token *)t_tmp->content)->type == PIPE)
	{
		t_tmp = t_tmp->next;
		take_redirection(t_tmp, cmd_tmp->next);
	}
	return (SUCCESS);
}

t_parse_cmd	*init_parser_cmd(t_list *token)
{
	t_parse_cmd	*cmd;
	t_list		*t_tmp;
	t_parse_cmd	*cmd_tmp;

	cmd = ft_calloc(1, sizeof(t_parse_cmd));
	if (!cmd)
		return (NULL);
	t_tmp = token;
	cmd_tmp = cmd;
	if (take_cmd(t_tmp, cmd_tmp) == FAILURE)
	{
		return (NULL);
	}
	t_tmp = token;
	cmd_tmp = cmd;
	if (take_redirection(t_tmp, cmd_tmp) == FAILURE)
	{
		return (NULL);
	}
	return (cmd);
}
