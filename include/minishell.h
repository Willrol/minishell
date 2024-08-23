/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:40:02 by aditer            #+#    #+#             */
/*   Updated: 2024/08/23 12:32:02 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/include/libft.h"
# include "minishell_struct.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>

# define FAILURE 0
# define SUCCESS 1

t_list		*init_env(char **envp);
void		print_env(t_list *env);
void		free_env(t_list *env);
char		**get_env_tab(t_list *env);
void		add_env(t_list **env, char *name, char *content);

typedef struct s_env
{
	char	*name;
	char	*content;
}			t_env;

#endif
