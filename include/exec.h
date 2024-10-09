/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 09:52:45 by aditer            #+#    #+#             */
/*   Updated: 2024/10/09 13:54:31 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "parse_cmd.h"

int		exec_builtin(t_list *env, t_minishell *shell, t_parse_cmd *cmd);
int		is_a_builtin(t_parse_cmd *cmd);
int		execution(t_list *env, t_minishell *shell, t_parse_cmd *cmd);
void	free_child(t_list *env, t_minishell *shell);
void	error_exec(char *str);
void	set_fd(t_minishell *shell);
int		handle_redirection(t_minishell *shell, t_parse_cmd *cmd);
int		exec_command(t_list *env, t_minishell *shell, t_parse_cmd *cmd);
void	exec_solo_builtin(t_list *env, t_minishell *shell, t_parse_cmd *tmp);
int		do_command(t_list *env, t_minishell *shell, t_parse_cmd *cmd);
void	search_here_doc(t_list *env, t_minishell *shell, t_parse_cmd *cmd);
void	unlink_here_doc(t_parse_cmd *cmd);

#endif