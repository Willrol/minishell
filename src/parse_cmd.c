/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rderkaza <rderkaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:18:40 by aditer            #+#    #+#             */
/*   Updated: 2024/10/14 14:58:10 by rderkaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cmd.h"

// void	print_parser_cmd(t_parse_cmd *cmd)
// {
// 	t_parse_cmd		*tmp;
// 	t_redirection	*redir;

// 	tmp = cmd;
// 	while (tmp)
// 	{
// 		printf("value: %s\n", tmp->value);
// 		printf("argc: %d\n", tmp->argc);
// 		printf("argv: ");
// 		for (int i = 0; i < tmp->argc; i++)
// 			printf("%s ", tmp->argv[i]);
// 		printf("\n");
// 		redir = tmp->redirection;
// 		while (redir)
// 		{
// 			printf("file_name: %s\n", redir->file_name);
// 			if (redir->type == APPEND)
// 				printf("type: APPEND\n");
// 			else if (redir->type == OUT)
// 				printf("type: OUT\n");
// 			else if (redir->type == HERE_DOC)
// 				printf("type: HERE_DOC\n");
// 			else if (redir->type == IN)
// 				printf("type: IN\n");
// 			redir = redir->next;
// 		}
// 		printf("______________________________________________\n");
// 		tmp = tmp->next;
// 	}
// }

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

t_parse_cmd	*store_words(t_list *tmp, t_parse_cmd *cmd)
{
	int			i;
	t_parse_cmd	*cmd_tmp;
	t_list		*t_tmp;

	i = 0;
	cmd_tmp = cmd;
	t_tmp = tmp;
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
	return (SUCCESS);
}

int	take_cmd(t_list *t_tmp, t_parse_cmd *cmd_tmp)
{
	cmd_tmp->argc = cpt_word(t_tmp);
	cmd_tmp->argv = ft_calloc(cmd_tmp->argc + 1, sizeof(char *));
	if (!cmd_tmp->argv)
		return (FAILURE);
	cmd_tmp->pid = -1;
	if (store_words(t_tmp, cmd_tmp) == NULL)
		return (FAILURE);
	if (t_tmp && ((t_token *)t_tmp->content)->type == PIPE && to_next_cmd(t_tmp,
			cmd_tmp) == FAILURE)
		return (FAILURE);
	if (cmd_tmp->argc > 0)
		cmd_tmp->value = ft_strdup(cmd_tmp->argv[0]);
	return (SUCCESS);
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
