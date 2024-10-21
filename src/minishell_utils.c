/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:56:55 by aditer            #+#    #+#             */
/*   Updated: 2024/10/21 17:58:09 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "parse_cmd.h"

char	*get_path(void)
{
	char	*path;
	char	**split;
	int		fd;

	fd = open("/etc/environment", O_RDONLY);
	if (fd == -1)
		return (NULL);
	path = get_next_line(fd);
	split = ft_split(path, '"');
	if (!split)
	{
		free(path);
		close(fd);
		return (NULL);
	}
	free(path);
	path = ft_strdup(split[1]);
	ft_free_tab(split);
	close(fd);
	return (path);
}

void	add_shlvl(t_list *env)
{
	t_list	*shlvl;
	char	*shlvl_str;
	int		shlvl_int;

	shlvl = search_env(env, "SHLVL");
	if (!shlvl)
		return ;
	shlvl_int = ft_atoi(((t_env *)shlvl->content)->content);
	shlvl_int++;
	shlvl_str = ft_itoa(shlvl_int);
	if (!shlvl_str)
		return ;
	free(((t_env *)shlvl->content)->content);
	((t_env *)shlvl->content)->content = shlvl_str;
}

void	here_exec(t_minishell *shell, t_parse_cmd *cmd, t_list *env)
{
	if (search_here_doc(env, shell, cmd) == FAILURE)
	{
		unlink_here_doc(cmd);
		free_parse_cmd(cmd);
		return ;
	}
	signal(SIGINT, handle);
	execution(env, shell, cmd);
	unlink_here_doc(cmd);
	free_parse_cmd(cmd);
	return ;
}

void	loop(t_minishell *shell, t_parse_cmd *cmd, t_list *token, t_list *env)
{
	char	*new_input;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	shell->cmd = NULL;
	new_input = init_input(env, *shell);
	if (!new_input)
		error_malloc(shell, env);
	token = lexer(new_input, 0);
	cmd = init_parser_cmd(token);
	if (cmd == NULL)
	{
		free_token_list(token);
		free(new_input);
		error_malloc(shell, env);
	}
	free(new_input);
	shell->cmd = cmd;
	free_token_list(token);
	minus_quote(cmd);
	expand(cmd, env, shell);
	here_exec(shell, cmd, env);
}

char	*get_username(void)
{
	struct utmp	user;
	int			fd;
	char		*username;

	fd = open("/var/run/utmp", O_RDONLY);
	if (fd == -1)
		return (NULL);
	username = "";
	while (read(fd, &user, sizeof(user)) > 0)
	{
		if (user.ut_type == USER_PROCESS)
		{
			username = ft_strdup(user.ut_user);
			if (!username)
			{
				close(fd);
				return (NULL);
			}
			break ;
		}
	}
	close(fd);
	return (username);
}
