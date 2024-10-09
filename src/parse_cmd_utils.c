/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:18:35 by rderkaza          #+#    #+#             */
/*   Updated: 2024/10/08 17:50:35 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cmd.h"

void	free_redirection(t_redirection *redir)
{
	t_redirection	*tmp;

	while (redir)
	{
		tmp = redir->next;
		if (redir->file_name)
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
		free_redirection(cmd->redirection);
	if (cmd->next)
		free_parse_cmd(cmd->next);
	free(cmd);
}

int	sign_chk(int type)
{
	if (type == APPEND || type == OUT || type == HERE_DOC || type == IN)
		return (1);
	return (0);
}

int	to_next_cmd(t_list *t_tmp, t_parse_cmd *cmd_tmp)
{
	cmd_tmp->next = ft_calloc(1, sizeof(t_parse_cmd));
	if (!cmd_tmp->next)
		return (FAILURE);
	cmd_tmp->pid = -1;
	t_tmp = t_tmp->next;
	take_cmd(t_tmp, cmd_tmp->next);
	return (SUCCESS);
}

void	add_last(t_redirection *redir, t_parse_cmd *cmd_tmp)
{
	t_redirection	*tmp;

	tmp = cmd_tmp->redirection;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = redir;
}
