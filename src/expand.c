/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:13:10 by aditer            #+#    #+#             */
/*   Updated: 2024/09/18 16:22:07 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cmd.h"

static int	get_end(char *str, int j)
{
	int	i;

	i = 1;
	while (str[j + i] && ft_isalnum(str[j + i]) == 1)
		i++;
	return (i);
}

static char	*dollar_expander(char *str, int *j, t_list *env)
{
	char	*tmp;
	char	*expand;
	char	*dollar;
	t_list	*exp_env;

	expand = "";
	dollar = ft_substr(str, *j, get_end(str, *j));
	exp_env = search_env(env, dollar + 1);
	if (exp_env != NULL)
		expand = ((t_env *)exp_env->content)->content;
	tmp = ft_str_replace(str, dollar, expand);
	free(dollar);
	*j += ft_strlen(expand) - 1;
	return (tmp);
}

void	search_dollar(char **argv, t_list *env)
{
	int	i;
	int	j;
	int	simple_quote;
	int	double_quote;

	i = 0;
	simple_quote = 0;
	double_quote = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j] != 0)
		{
			if (argv[i][j] == '\'' && !double_quote)
				simple_quote = !simple_quote;
			if (argv[i][j] == '"' && !simple_quote)
				double_quote = !double_quote;
			if (argv[i][j] == '$' && !simple_quote && ft_iswhitespace(argv[i][j
					+ 1]) == 0 && argv[i][j + 1] != 0)
				argv[i] = dollar_expander(argv[i], &j, env);
			j++;
		}
		i++;
	}
}

void	expand(t_parse_cmd *cmd, t_list *env)
{
	while (cmd)
	{
		search_dollar(cmd->argv, env);
		free(cmd->value);
		remove_quote(cmd->argv);
		cmd->value = ft_strdup(cmd->argv[0]);
		cmd = cmd->next;
	}
}
