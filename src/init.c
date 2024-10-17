/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:07:26 by rderkaza          #+#    #+#             */
/*   Updated: 2024/10/17 08:02:01 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "parse_cmd.h"

char	*init_input(t_list *env, t_minishell shell)
{
	char	*input;
	char	*new_input;

	input = read_input(env, shell);
	new_input = ft_strtrim(input, " ");
	free(input);
	return (new_input);
}

void	init_shell_env(t_minishell *shell, t_list **env, char **envp)
{
	char	*pwd;

	shell->exit_status = 0;
	shell->username = get_username();
	shell->path = NULL;
	if (!shell->username)
		error_malloc(shell, NULL);
	if (!envp || !*envp)
	{
		shell->path = get_path();
		if (!shell->path)
			error_malloc(shell, NULL);
		pwd = getcwd(NULL, 0);
		if (add_env(env, "PWD", pwd) == FAILURE)
			error_malloc(shell, *env);
		free(pwd);
		if (add_env(env, "SHLVL", "0") == FAILURE)
			error_malloc(shell, *env);
		if (add_env(env, "_", "/usr/bin/env") == FAILURE)
			error_malloc(shell, *env);
	}
	else
		*env = init_env(shell, envp, -1);
}

char	*read_input(t_list *env, t_minishell shell)
{
	char	*line;

	line = readline("minishell$ ");
	if (!line)
	{
		ft_putstr_fd("exit\n", 1);
		free(shell.username);
		free(shell.path);
		free_env(env);
		exit(0);
	}
	add_history(line);
	return (line);
}
