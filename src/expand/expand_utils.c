/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:31:09 by aditer            #+#    #+#             */
/*   Updated: 2024/10/18 13:00:40 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cmd.h"

int	ft_strlen_nowhitespace(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (ft_iswhitespace(str[i]) == 0)
			len++;
		i++;
	}
	return (len);
}

int	get_end(char *str, int j)
{
	int	i;

	i = 1;
	while (str[j + i] && ft_isalnum(str[j + i]) == 1)
		i++;
	return (i);
}

char	*tilde_expander(char *str, t_list *env, char *username, int *j)
{
	char	*tmp;
	char	*expanded_tilde;
	t_list	*node;

	node = search_env(env, "HOME");
	if (node)
		expanded_tilde = ft_strdup(((t_env *)node->content)->content);
	if (!node)
		expanded_tilde = ft_strjoin("/home/", username);
	if (!expanded_tilde)
		return (NULL);
	tmp = ft_str_replace(str, "~", expanded_tilde);
	free(expanded_tilde);
	if (!tmp)
		return (NULL);
	*j += ft_strlen(username) - 1;
	return (tmp);
}

char	*question_mark_expander(char *str, int *j, t_minishell *shell)
{
	char	*tmp;
	char	*expand;

	expand = ft_itoa(shell->exit_status);
	if (!expand)
		return (NULL);
	tmp = ft_str_replace(str, "$?", expand);
	if (!tmp)
	{
		free(expand);
		return (NULL);
	}
	*j += ft_strlen(expand) - 1;
	free(expand);
	return (tmp);
}

int	quote_state(char c, int quoted)
{
	if (c == ('\'' * -1) && !(quoted & 0b10))
		quoted ^= 0b01;
	if (c == ('"' * -1) && !(quoted & 0b01))
		quoted ^= 0b10;
	return (quoted);
}
