/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:26:48 by rderkaza          #+#    #+#             */
/*   Updated: 2024/10/22 14:54:01 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	here_parent(pid_t pid, t_minishell *shell)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
	else if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	if (shell->exit_status == 130)
		return (FAILURE);
	return (SUCCESS);
}

void	update_redir_file_name(t_redirection *redir, int i, void *shell,
		void *env)
{
	char	*nb;

	nb = ft_itoa(i);
	if (!nb)
		error_malloc(shell, env);
	free(redir->file_name);
	redir->file_name = ft_strjoin(".tmp", nb);
	free(nb);
	if (!redir->file_name)
		error_malloc(shell, env);
}
