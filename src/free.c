/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rderkaza <rderkaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:43:12 by aditer            #+#    #+#             */
/*   Updated: 2024/10/11 15:36:24 by rderkaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse_cmd.h"

void	free_shell(t_minishell *shell, t_list *env)
{
	if (shell->username)
		free(shell->username);
	if (shell->cmd != NULL)
	{
		free_parse_cmd(shell->cmd);
	}
	if (env)
		free_env(env);
	if (shell->fd_save != -1)
		close(shell->fd_save);
	if (shell->path)
		free(shell->path);
}

void	free_env(t_list *env)
{
	t_list	*tmp;

	tmp = env;
	while (env)
	{
		tmp = env->next;
		if (((t_env *)env->content)->name)
			free(((t_env *)env->content)->name);
		if (((t_env *)env->content)->content)
			free(((t_env *)env->content)->content);
		if (env->content)
			free(env->content);
		free(env);
		env = tmp;
	}
}

void	free_tmps(char *tab1, char *tab2)
{
	free(tab1);
	free(tab2);
}
