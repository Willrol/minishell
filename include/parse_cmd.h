/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rderkaza <rderkaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:40:03 by aditer            #+#    #+#             */
/*   Updated: 2024/09/16 11:21:51 by rderkaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_CMD_H
# define PARSE_CMD_H

# include "minishell.h"

typedef struct s_redirection
{
	char					*file_name;
	int						type;
	struct s_redirection	*next;

}							t_redirection;

typedef struct s_parse_cmd
{
	char					*value;
	char					**argv;
	int						argc;
	pid_t					pid;
	t_redirection			*redirection;
	struct s_parse_cmd		*next;
}							t_parse_cmd;

void	take_cmd(t_list *t_tmp, t_parse_cmd *cmd_tmp);
void	free_redirection(t_redirection *redir);
void	free_parse_cmd(t_parse_cmd *cmd);
int		sign_chk(int type);
int		to_next_cmd(t_list *t_tmp, t_parse_cmd *cmd_tmp);
void	add_last(t_redirection *redir, t_parse_cmd *cmd_tmp);

#endif