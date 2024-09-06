/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:40:02 by aditer            #+#    #+#             */
/*   Updated: 2024/09/05 16:08:01 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/include/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>

# define FAILURE -1
# define SUCCESS 0

typedef enum e_valuetype
{
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	DOLLAR_SIGN,
	PIPE,
	DOUBLE_GREATER_THAN,
	GREATER_THAN,
	DOUBLE_LESS_THAN,
	LESS_THAN,
	DEFAULT
}			t_valuetype;

typedef struct s_env
{
	char	*name;
	char	*content;
}			t_env;

typedef struct s_token
{
	char	*value;
	int		type;

}			t_token;

t_list		*init_env(char **envp);
void		print_env(t_list *env);
void		free_env(t_list *env);
char		**get_env_tab(t_list *env);
t_list		*search_env(t_list *env, char *name);
void		add_env(t_list **env, char *name, char *content);
void		remove_env(t_list **env, char *name);

void		lexer(char *line);
void		print_token(t_list *token);
void		free_token_list(t_list *token);
int			isnotsp(char *line);
int			ft_mot(char *line);
void		lexer_error(t_list **token, t_token *node_token);
t_valuetype	typval(char *value);

void		cd(int argc, char **argv, t_list *env);
void		pwd(void);
void		echo(int argc, char **argv);
void		print_env(t_list *env);

#endif
