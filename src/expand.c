/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:13:10 by aditer            #+#    #+#             */
/*   Updated: 2024/10/08 14:29:34 by aditer           ###   ########.fr       */
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

void	search_dollar(char **argv, t_list *env, t_minishell *shell)
{
	int	i;
	int	j;
	int	simple_quote;
	int	double_quote;

	i = -1;
	simple_quote = 0;
	double_quote = 0;
	(void)shell;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j] != 0)
		{
			if (argv[i][j] == '~' && ft_strlen_nowhitespace(argv[i]) == 1)
				argv[i] = tilde_expander(argv[i], env, shell->username, &j);
			if (argv[i] == NULL)
				free_shell(shell, env);
			if (argv[i][j] == '\'' && !double_quote)
				simple_quote = !simple_quote;
			if (argv[i][j] == '"' && !simple_quote)
				double_quote = !double_quote;
			if (argv[i][j] == '$' && !simple_quote && ft_iswhitespace(argv[i][j
					+ 1]) == 0 && argv[i][j + 1] != 0 && argv[i][j + 1] != '~')
				argv[i] = dollar_expander(argv[i], &j, env, shell);
			if (!argv[i])
				free_shell(shell, env);
		}
	}
}

void	expand(t_parse_cmd *cmd, t_list *env, t_minishell *shell)
{
	while (cmd)
	{
		if (cmd->argc == 0)
		{
			expand_redir(cmd, env, shell);
			cmd = cmd->next;
			continue ;
		}
		search_dollar(cmd->argv, env, shell);
		if (split_expand(&cmd->argc, &cmd->argv) == FAILURE)
			free_shell(shell, env);
		if (remove_quote(cmd->argv) == FAILURE)
			free_shell(shell, env);
		free(cmd->value);
		cmd->value = ft_strdup(cmd->argv[0]);
		expand_redir(cmd, env, shell);
		cmd = cmd->next;
	}
}
