/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:40:02 by aditer            #+#    #+#             */
/*   Updated: 2024/10/16 13:59:27 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/include/libft.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <unistd.h>
# include <utmp.h>

# define FAILURE -1
# define SUCCESS 0
# define WRITE 1
# define READ 0

extern int					g_sigflag;

typedef enum e_valuetype
{
	WORD,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	DOLLAR,
	PIPE,
	APPEND,
	OUT,
	HERE_DOC,
	IN,
}							t_valuetype;

typedef struct s_parse_cmd	t_parse_cmd;

typedef struct s_minishell
{
	char					*username;
	char					*path;
	unsigned char			exit_status;
	int						pipe_fd[2];
	int						prev_pipe_fd_out;
	int						fd_in;
	int						fd_out;
	int						fd_save;
	t_parse_cmd				*cmd;
	t_list					**env;
}							t_minishell;

typedef struct s_env
{
	char					*name;
	char					*content;
}							t_env;

typedef struct s_token
{
	char					*value;
	int						type;

}							t_token;

t_list						*init_env(t_minishell *shell, char **envp, int i);
char						*init_input(t_list *env, t_minishell shell);
void						init_shell_env(t_minishell *shell, t_list **env,
								char **envp);
char						*get_path(void);
char						*read_input(t_list *env, t_minishell shell);

char						**get_env_tab(t_list *env);
t_list						*search_env(t_list *env, char *name);
int							add_env(t_list **env, char *name, char *content);
int							remove_env(t_list **env, char *str);
int							unset(t_list **env, char **argv);
char						*get_username(void);

t_list						*lexer(char *line, int err);
void						print_token(t_list *token);
void						free_token_list(t_list *token);
void						free_backup(t_minishell backup);
int							isnotsp(char *line);
int							ft_mot(char *line);
void						lexer_error(t_list **token, t_token *node_token);
t_valuetype					typval(char *value);

int							cd(int argc, char **argv, t_list *env);
int							pwd(void);
int							echo(int argc, char **argv);
int							print_env(t_list *env);
int							ft_export(t_list **env, char **argv);
int							exit_builtin(t_list *env, t_minishell *shell,
								t_parse_cmd *cmd);
void						error_print(char *str, char *cmd_name);
void						error_malloc(t_minishell *shell, t_list *env);

void						handle_sigint(int sig);
void						handle(int sig);
void						handle_sigquit(int sig);

void						free_env(t_list *env);
void						free_shell(t_minishell *shell, t_list *env);
void						free_tmps(char *tab1, char *tab2);
char						*read_input(t_list *env, t_minishell shell);

void						loop(t_minishell *shell, t_parse_cmd *cmd,
								t_list *token, t_list *env);
void						here_exec(t_minishell *shell, t_parse_cmd *cmd,
								t_list *env);
void						add_shlvl(t_list *env);
char						*get_path(void);

#endif
