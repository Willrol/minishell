/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 09:52:45 by aditer            #+#    #+#             */
/*   Updated: 2024/10/21 13:49:32 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "parse_cmd.h"
# include <signal.h>
# include <sys/types.h>
# include <dirent.h>

void	free_child(t_list *env, t_minishell *shell);
void	error_exec(char *str, int error);

void	set_fd(t_minishell *shell);
int		execution(t_list *env, t_minishell *shell, t_parse_cmd *cmd);
int		exec_command(t_list *env, t_minishell *shell, t_parse_cmd *cmd);
int		is_a_builtin(t_parse_cmd *cmd);
int		exec_builtin(t_minishell *shell, t_parse_cmd *cmd);
void	exec_solo_builtin(t_minishell *shell, t_parse_cmd *tmp);
int		do_command(t_list *env, t_minishell *shell, t_parse_cmd *cmd);

int		search_here_doc(t_list *env, t_minishell *shell, t_parse_cmd *cmd);
int		here_parent(pid_t pid, t_minishell *shell);
void	unlink_here_doc(t_parse_cmd *cmd);
int		handle_redirection(t_minishell *shell, t_parse_cmd *cmd);
void	handle_here_doc(int sig);

void	handle_sigint_hd(int sig);
void	handle(int sig);
void	handle_sigint(int sig);
void	handle_sigquit(int sig);

#endif