/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:34:54 by aditer            #+#    #+#             */
/*   Updated: 2024/10/22 14:29:41 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	active_doc(t_redirection *redirection, int fd)
{
	char	*line;

	while (1)
	{
		if (g_sigflag == 1)
		{
			break ;
		}
		line = readline("> ");
		if (!line || !ft_strcmp(line, redirection->file_name)
			|| g_sigflag == SIGINT)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

void	here_doc(t_list *env, t_minishell *shell, t_redirection *redirection,
		int i)
{
	int		fd;
	char	*nb;
	char	*file_name;

	signal(SIGINT, handle_here_doc);
	nb = ft_itoa(i);
	if (!nb)
		error_malloc(shell, env);
	file_name = ft_strjoin(".tmp", nb);
	free(nb);
	if (!file_name)
		error_malloc(shell, env);
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(file_name);
	if (fd == -1)
	{
		error_exec("here_doc", 0);
		return ;
	}
	active_doc(redirection, fd);
	close(fd);
	free_child(env, shell);
	if (g_sigflag == SIGINT)
		exit(130);
	exit(0);
}

int	call_doc(t_list *env, t_minishell *shell, t_redirection *redir, int i)
{
	pid_t	pid;

	g_sigflag = 0;
	pid = fork();
	if (pid == -1)
		error_exec("fork", 0);
	if (pid == 0)
		here_doc(env, shell, redir, i);
	else if (here_parent(pid, shell) == FAILURE)
	{
		update_redir_file_name(redir, i, shell, env);
		return (FAILURE);
	}
	update_redir_file_name(redir, i, shell, env);
	return (SUCCESS);
}

int	search_here_doc(t_list *env, t_minishell *shell, t_parse_cmd *cmd)
{
	t_parse_cmd		*tmp;
	t_redirection	*redir;
	int				i;

	tmp = cmd;
	i = 0;
	while (tmp)
	{
		redir = tmp->redirection;
		while (redir)
		{
			if (redir->type == HERE_DOC)
			{
				if (call_doc(env, shell, redir, i) == FAILURE)
				{
					return (FAILURE);
				}
			}
			i++;
			redir = redir->next;
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

void	unlink_here_doc(t_parse_cmd *cmd)
{
	t_parse_cmd		*tmp;
	t_redirection	*redir;

	tmp = cmd;
	while (tmp)
	{
		redir = tmp->redirection;
		while (redir)
		{
			if (redir->type == HERE_DOC)
				unlink(redir->file_name);
			redir = redir->next;
		}
		tmp = tmp->next;
	}
}
