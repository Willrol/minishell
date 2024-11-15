/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:13:10 by aditer            #+#    #+#             */
/*   Updated: 2024/10/22 13:24:15 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cmd.h"

static char	*dollar_expander(char *str, int *j, t_list *env, t_minishell *shell)
{
	char	*tmp;
	char	*expand;
	char	*dollar;
	t_list	*exp_env;

	if (str[*j + 1] == '?')
	{
		tmp = question_mark_expander(str, j, shell);
		if (!tmp)
			return (NULL);
		return (tmp);
	}
	expand = "";
	dollar = ft_substr(str, *j, get_end(str, *j));
	if (!dollar)
		return (NULL);
	exp_env = search_env(env, dollar + 1);
	if (exp_env != NULL)
		expand = ((t_env *)exp_env->content)->content;
	tmp = ft_str_replace(str, dollar, expand);
	free(dollar);
	if (!tmp)
		return (NULL);
	*j += ft_strlen(expand) - 1;
	return (tmp);
}

static bool	is_expandable(char *argv, int j, int quoted, bool *is_expand)
{
	if (argv[j] == '$' && !(quoted & 0b01) && ft_iswhitespace(argv[j + 1]) == 0
		&& argv[j + 1] != 0 && argv[j + 1] != '~' && argv[j + 1] != ('"' * -1))
	{
		*is_expand = true;
		return (true);
	}
	return (false);
}

void	search_dollar(char **argv, t_list *env, t_minishell *shell,
		bool *is_expand)
{
	int	i;
	int	j;
	int	quoted;

	i = -1;
	quoted = 0;
	(void)shell;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j] != 0)
		{
			if (argv[i][j] == '~' && ft_strlen_nowhitespace(argv[i]) == 1)
				argv[i] = tilde_expander(argv[i], env, shell->username, &j);
			if (!argv[i])
				error_malloc(shell, env);
			if (is_expandable(argv[i], j, quoted, is_expand))
				argv[i] = dollar_expander(argv[i], &j, env, shell);
			if (argv[i] == NULL)
				error_malloc(shell, env);
			if (j >= 0)
				quoted = quote_state(argv[i][j], quoted);
		}
		check_argv_empty(&argv[i]);
	}
}

void	expand(t_parse_cmd *cmd, t_list *env, t_minishell *shell)
{
	bool	is_expand;

	while (cmd)
	{
		is_expand = false;
		if (cmd->argc == 0)
		{
			expand_redir(cmd, env, shell);
			cmd = cmd->next;
			continue ;
		}
		search_dollar(cmd->argv, env, shell, &is_expand);
		if (is_expand == true)
			if (split_expand(&cmd->argc, &cmd->argv) == FAILURE)
				error_malloc(shell, env);
		if (remove_quote(cmd->argv) == FAILURE)
			error_malloc(shell, env);
		if (cmd->argc > 0)
			rm_argv_null(&cmd->argc, &cmd->argv);
		free(cmd->value);
		cmd->value = ft_strdup(cmd->argv[0]);
		expand_redir(cmd, env, shell);
		cmd = cmd->next;
	}
}
