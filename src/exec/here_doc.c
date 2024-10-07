/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rderkaza <rderkaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:34:54 by aditer            #+#    #+#             */
/*   Updated: 2024/10/07 16:31:16 by rderkaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	active_doc(t_redirection *redirection, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, redirection->file_name))
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

	nb = ft_itoa(i);
	file_name = ft_strjoin(".tmp", nb);
	free(nb);
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(file_name);
	if (fd == -1)
	{
		error_exec("here_doc");
		return ;
	}
	active_doc(redirection, fd);
	close(fd);
	free_child(env, shell);
	exit(0);
}

void	call_doc(t_list *env, t_minishell *shell, t_redirection *redir, int i)
{
	pid_t	pid;
	char	*nb;

	pid = fork();
	if (pid == -1)
		error_exec("fork");
	if (pid == 0)
		here_doc(env, shell, redir, i);
	else
		waitpid(pid, NULL, 0);
	nb = ft_itoa(i);
	free(redir->file_name);
	redir->file_name = ft_strjoin(".tmp", nb);
	free(nb);
}

void	search_here_doc(t_list *env, t_minishell *shell, t_parse_cmd *cmd)
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
				call_doc(env, shell, redir, i);
			}
			i++;
			redir = redir->next;
		}
		tmp = tmp->next;
	}
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
