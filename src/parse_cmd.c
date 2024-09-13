/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:18:40 by aditer            #+#    #+#             */
/*   Updated: 2024/09/13 14:44:31 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cmd.h"

void	free_redirectiuon(t_redirection *redir)
{
	t_redirection	*tmp;

	while (redir)
	{
		printf("free redirection\n");
		tmp = redir->next;
		free(redir->file_name);
		free(redir);
		redir = tmp;
	}
}

void	free_parse_cmd(t_parse_cmd *cmd)
{
	int	i;

	if (cmd == NULL)
		return ;
	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i])
		{
			free(cmd->argv[i]);
			i++;
		}
		free(cmd->argv);
	}
	if (cmd->value)
		free(cmd->value);
	if (cmd->redirection)
		free_redirectiuon(cmd->redirection);
	if (cmd->next)
		free_parse_cmd(cmd->next);
	free(cmd);
}

void	print_parser_cmd(t_parse_cmd *cmd)
{
	t_parse_cmd		*tmp;
	t_redirection	*redir;

	tmp = cmd;
	while (tmp)
	{
		printf("value: %s\n", tmp->value);
		printf("argc: %d\n", tmp->argc);
		printf("argv: ");
		for (int i = 0; i < tmp->argc; i++)
			printf("%s ", tmp->argv[i]);
		printf("\n");
		redir = tmp->redirection;
		while (redir)
		{
			printf("file_name: %s\n", redir->file_name);
			printf("type: %d\n", redir->type);
			redir = redir->next;
		}
		tmp = tmp->next;
	}
}

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

void	take_cmd(t_list *token, t_parse_cmd *cmd)
{
	int			i;
	t_list		*token_tmp;
	t_parse_cmd	*cmd_tmp;

	token_tmp = token;
	cmd_tmp = cmd;
	i = -1;
	cmd_tmp->argc = cpt_word(token_tmp);
	cmd_tmp->argv = calloc(cmd_tmp->argc + 1, sizeof(char *));
	if (!cmd_tmp->argv)
		return ;
	cmd_tmp->pid = -1;
	while (token_tmp && ((t_token *)token_tmp->content)->type != PIPE)
	{
		if (((t_token *)token_tmp->content)->type == APPEND
			|| ((t_token *)token_tmp->content)->type == OUT
			|| ((t_token *)token_tmp->content)->type == HERE_DOC
			|| ((t_token *)token_tmp->content)->type == IN)
			token_tmp = token_tmp->next;
		else if (((t_token *)token_tmp->content)->type == WORD)
			cmd_tmp->argv[++i] = ft_strdup(((t_token *)token_tmp->content)->value);
		cmd_tmp->argv[i] = NULL;
		token_tmp = token_tmp->next;
	}
	if (token_tmp && ((t_token *)token_tmp->content)->type == PIPE)
	{
		cmd_tmp->next = calloc(1, sizeof(t_parse_cmd));
		if (!cmd_tmp->next)
			return ;
		cmd_tmp->pid = -1;
		token_tmp = token_tmp->next;
		take_cmd(token_tmp, cmd_tmp->next);
	}
	if (cmd_tmp->argc > 0)
		cmd_tmp->value = ft_strdup(cmd_tmp->argv[0]);
}

void	take_redirection(t_list *token, t_parse_cmd *cmd)
{
	t_list			*token_tmp;
	t_parse_cmd		*cmd_tmp;
	t_redirection	*redir;
	t_redirection	*tmp;

	token_tmp = token;
	cmd_tmp = cmd;
	while (token_tmp && ((t_token *)token_tmp->content)->type != PIPE)
	{
		if (((t_token *)token_tmp->content)->type == APPEND
			|| ((t_token *)token_tmp->content)->type == OUT
			|| ((t_token *)token_tmp->content)->type == HERE_DOC
			|| ((t_token *)token_tmp->content)->type == IN)
		{
			redir = calloc(1, sizeof(t_redirection));
			if (!redir)
				return ;
			redir->type = ((t_token *)token_tmp->content)->type;
			token_tmp = token_tmp->next;
			redir->file_name = ft_strdup(((t_token *)token_tmp->content)->value);
			redir->next = NULL;
			if (cmd_tmp->redirection == NULL)
				cmd_tmp->redirection = redir;
			else
			{
				tmp = cmd_tmp->redirection;
				while (tmp->next != NULL)
					tmp = tmp->next;
				tmp->next = redir;
			}
		}
		token_tmp = token_tmp->next;
	}
	if (token_tmp && ((t_token *)token_tmp->content)->type == PIPE)
	{
		token_tmp = token_tmp->next;
		take_redirection(token_tmp, cmd_tmp->next);
	}
}

void	init_parser_cmd(t_list *token)
{
	t_parse_cmd	*cmd;

	cmd = calloc(1, sizeof(t_parse_cmd));
	if (!cmd)
		return ;
	take_cmd(token, cmd);
	take_redirection(token, cmd);
	print_parser_cmd(cmd);
	free_parse_cmd(cmd);
}
