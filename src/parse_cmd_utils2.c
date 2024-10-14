/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rderkaza <rderkaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:54:52 by rderkaza          #+#    #+#             */
/*   Updated: 2024/10/14 14:46:41 by rderkaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cmd.h"

void	append_redir(t_redirection *redir, t_parse_cmd *cmd_tmp)
{
	if (cmd_tmp->redirection == NULL)
		cmd_tmp->redirection = redir;
	else
		add_last(redir, cmd_tmp);
}
