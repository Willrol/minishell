/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rderkaza <rderkaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:40:03 by aditer            #+#    #+#             */
/*   Updated: 2024/10/11 15:55:17 by rderkaza         ###   ########.fr       */
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

int							take_cmd(t_list *t_tmp, t_parse_cmd *cmd_tmp);
void						free_redirection(t_redirection *redir);
void						free_parse_cmd(t_parse_cmd *cmd);
int							sign_chk(int type);
int							to_next_cmd(t_list *t_tmp, t_parse_cmd *cmd_tmp);
void						add_last(t_redirection *redir,
								t_parse_cmd *cmd_tmp);
t_parse_cmd					*init_parser_cmd(t_list *token);
void						expand(t_parse_cmd *cmd, t_list *env,
								t_minishell *shell);
void						expand_redir(t_parse_cmd *cmd, t_list *env,
								t_minishell *shell);

void						print_parser_cmd(t_parse_cmd *cmd);
int							remove_quote(char **argv);
int							remove_quote_redir(char **file_name);
int							ft_strlen_nowhitespace(char *str);
int							get_end(char *str, int j);
char						*tilde_expander(char *str, t_list *env,
								char *username, int *j);
char						*question_mark_expander(char *str, int *j,
								t_minishell *shell);
int							split_expand(int *argc, char ***argv, int i);

#endif