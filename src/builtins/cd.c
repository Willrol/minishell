/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:53:28 by aditer            #+#    #+#             */
/*   Updated: 2024/10/23 09:04:15 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

int	cd_home(t_list *env)
{
	t_list	*node_env;
	t_list	*oldpwd;
	char	*cwd;

	node_env = search_env(env, "HOME");
	if (!node_env)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	if (chdir(((t_env *)node_env->content)->content) == -1)
	{
		ft_putstr_fd("cd: No such file or directory\n", 2);
		return (1);
	}
	oldpwd = search_env(env, "PWD");
	if (oldpwd)
		add_env(&env, "OLDPWD", ((t_env *)oldpwd->content)->content);
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		add_env(&env, "PWD", cwd);
		free(cwd);
	}
	return (SUCCESS);
}

int	print_error(int flag)
{
	if (flag == 1)
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
	else
		ft_putstr_fd("cd: No such file or directory\n", 2);
	return (1);
}

int	cd_tiret(t_list *env)
{
	t_list	*oldpwd;
	t_list	*pwd;
	char	*cwd;

	pwd = search_env(env, "OLDPWD");
	if (!pwd)
		return (print_error(1));
	if (chdir(((t_env *)pwd->content)->content) == -1)
		return (print_error(2));
	oldpwd = search_env(env, "PWD");
	if (!oldpwd)
	{
		remove_env(&env, "OLDPWD");
		return (SUCCESS);
	}
	if (oldpwd)
		add_env(&env, "OLDPWD", ((t_env *)oldpwd->content)->content);
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		add_env(&env, "PWD", cwd);
		ft_putendl_fd(cwd, 1);
		free(cwd);
	}
	return (SUCCESS);
}

int	cd_arg(t_list *env, char *path)
{
	t_list	*oldpwd;
	char	*cwd;

	if (chdir(path) == -1)
	{
		error_print(path, "cd");
		return (1);
	}
	oldpwd = search_env(env, "PWD");
	if (oldpwd)
		add_env(&env, "OLDPWD", ((t_env *)oldpwd->content)->content);
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		add_env(&env, "PWD", cwd);
		free(cwd);
	}
	return (SUCCESS);
}

int	cd(int argc, char **argv, t_list *env)
{
	if (argc == 1)
		return (cd_home(env));
	else if (argc == 2 && !ft_strncmp(argv[1], "-", 1))
		return (cd_tiret(env));
	else if (argc == 2)
		return (cd_arg(env, argv[1]));
	else
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
}
