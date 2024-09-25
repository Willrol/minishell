/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:16:09 by aditer            #+#    #+#             */
/*   Updated: 2024/09/25 08:41:24 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cmd.h"

static char	*dollar_expander_redir(char *str, int *i, t_list *env)
{
	char	*tmp;
	char	*expand;
	char	*dollar;
	t_list	*exp_env;

	expand = "";
	dollar = ft_substr(str, *i, get_end(str, *i));
	exp_env = search_env(env, dollar + 1);
	if (exp_env != NULL)
		expand = ((t_env *)exp_env->content)->content;
	tmp = ft_str_replace(str, dollar, expand);
	free(dollar);
	*i += ft_strlen(expand) - 1;
	return (tmp);
}

void	search_dollar_redir(char **file_name, t_list *env, t_minishell backup)
{
	int	i;
	int	simple_quote;
	int	double_quote;

	i = 0;
	simple_quote = 0;
	double_quote = 0;
	(void)backup;
	while ((*file_name)[i] != 0)
	{
		if ((*file_name)[i] == '~' && ft_strlen_nowhitespace(*file_name) == 1)
			*file_name = tilde_expander(*file_name, backup.username, &i);
		if ((*file_name)[i] == '\'' && !double_quote)
			simple_quote = !simple_quote;
		if ((*file_name)[i] == '"' && !simple_quote)
			double_quote = !double_quote;
		if ((*file_name)[i] == '$' && !simple_quote
			&& ft_iswhitespace((*file_name)[i + 1]) == 0 && (*file_name)[i
			+ 1] != 0 && (*file_name)[i + 1] != '~')
			*file_name = dollar_expander_redir(*file_name, &i, env);
		i++;
	}
}

void	expand_redir(t_parse_cmd *cmd, t_list *env, t_minishell backup)
{
	t_redirection	*current_redir;

	current_redir = cmd->redirection;
	while (current_redir)
	{
		if (current_redir->file_name)
		{
			search_dollar_redir(&(current_redir->file_name), env, backup);
			remove_quote_redir(&(current_redir->file_name));
		}
		current_redir = current_redir->next;
	}
}
