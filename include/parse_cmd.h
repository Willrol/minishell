/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:40:03 by aditer            #+#    #+#             */
/*   Updated: 2024/10/17 10:36:39 by aditer           ###   ########.fr       */
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

void						free_redirection(t_redirection *redir);
void						free_parse_cmd(t_parse_cmd *cmd);
void						ft_free_tabs(char **split, char **new_argv);

int							sign_chk(int type);
void						add_last(t_redirection *redir,
								t_parse_cmd *cmd_tmp);
int							ft_strlen_nowhitespace(char *str);
int							get_end(char *str, int j);

void						append_redir(t_redirection *redir,
								t_parse_cmd *cmd_tmp);
void						expand_redir(t_parse_cmd *cmd, t_list *env,
								t_minishell *shell);

int							take_cmd(t_list *t_tmp, t_parse_cmd *cmd_tmp);
t_parse_cmd					*init_parser_cmd(t_list *token);
int							to_next_cmd(t_list *t_tmp, t_parse_cmd *cmd_tmp);

void						expand(t_parse_cmd *cmd, t_list *env,
								t_minishell *shell);
char						*tilde_expander(char *str, t_list *env,
								char *username, int *j);
char						*question_mark_expander(char *str, int *j,
								t_minishell *shell);
int							split_expand(int *argc, char ***argv);

void						is_quote(char c, bool *in_single_quote,
								bool *in_double_quote);
int							remove_quote(char **argv);
int							remove_quote_redir(char **file_name);

int							count_word(const char *str);
void						check_argv(char ***argv, char **new_argv);
void						trim_argv(char ***argv);

#endif