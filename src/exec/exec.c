/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:08:22 by aditer            #+#    #+#             */
/*   Updated: 2024/09/25 09:00:25 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse_cmd.h"

int	execution(t_list *env, t_minishell *shell, t_parse_cmd *cmd)
{
	bool pipe;
	t_parse_cmd *tmp;
	// int		old_in;

	(void)shell;
	if (!cmd->value)
		return (SUCCESS);
	tmp = cmd;
	pipe = tmp->next != NULL;
	// old_in = dup(STDIN_FILENO);
	while (tmp)
	{
		if (!pipe)
		{
			// dup2(old_in, STDIN_FILENO);
			// close(old_in);
			// command seul
			shell->exit_status = is_a_builtin(env, tmp);
		}
		else if (tmp->next == NULL)
		{
			// le derneir pipe
			
		}
		else
		{
			// avant le dernier pipe
				
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}