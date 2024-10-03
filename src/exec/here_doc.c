/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:34:54 by aditer            #+#    #+#             */
/*   Updated: 2024/10/03 14:36:55 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	here_doc(t_list *env, t_minishell *shell, t_redirection *redirection,
		int i)
{
	int		fd;
	char	*line;
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
	close(fd);
	free_child(env, shell);
	exit(0);
}

void	search_here_doc(t_list *env, t_minishell *shell, t_parse_cmd *cmd)
{
	t_parse_cmd		*tmp;
	t_redirection	*redir;
	pid_t			pid;
	int				i;
	char			*nb;

	tmp = cmd;
	i = 0;
	while (tmp)
	{
		redir = tmp->redirection;
		while (redir)
		{
			if (redir->type == HERE_DOC)
			{
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
			i++;
			redir = redir->next;
		}
		tmp = tmp->next;
	}
}

void	unlink_here_doc(t_parse_cmd *cmd)
{
	t_parse_cmd *tmp;
	t_redirection *redir;

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