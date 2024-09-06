/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:40:03 by aditer            #+#    #+#             */
/*   Updated: 2024/09/06 12:53:06 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "minishell.h"

typedef struct s_redirection
{
	char				*file;
	int					type;
	t_redirection		*next;

}						t_redirection;

typedef struct s_ast_value
{
	char				*value;
	char				**argv;
	int					argc;
	pid_t				pid;
	t_redirection		*redirection;
	struct t_ast_value	*next;
}						t_ast_value;

#endif
