/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rderkaza <rderkaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:26:48 by rderkaza          #+#    #+#             */
/*   Updated: 2024/10/14 16:41:34 by rderkaza         ###   ########.fr       */
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
