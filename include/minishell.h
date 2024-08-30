/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:40:02 by aditer            #+#    #+#             */
/*   Updated: 2024/08/30 13:11:59 by aditer           ###   ########.fr       */
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
	SINGLE_QUOTE = 1,
	DOUBLE_QUOTE = 2,
	DOLLAR_SIGN = 3,
	PIPE = 4,
	DOUBLE_GREATER_THAN = 5,
	GREATER_THAN = 6,
	DOUBLE_LESS_THAN = 7,
	LESS_THAN = 8,
	DEFAULT = 9
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
void		add_env(t_list **env, char *name, char *content);
void		remove_env(t_list **env, char *name);
void		lexer(char *line);
void		print_token(t_list *token);
void		free_token_list(t_list *token);
int			isnotsp(char *line);
int			ft_mot(char *line);
void		lexer_error(t_list **token, t_token *node_token);
t_valuetype	typval(char *value);

#endif
