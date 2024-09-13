/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:40:03 by aditer            #+#    #+#             */
/*   Updated: 2024/09/13 12:55:49 by aditer           ###   ########.fr       */
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

#endif