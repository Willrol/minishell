/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 08:20:58 by aditer            #+#    #+#             */
/*   Updated: 2024/10/08 11:45:30 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_malloc(t_list *env, t_minishell *shell, t_parse_cmd *cmd)
{
	if (shell)
		free_shell(shell, env);
	ft_putstr_fd("Error: Malloc failed.\n", 2);
	exit(1);
}