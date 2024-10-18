/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expand_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:27:37 by aditer            #+#    #+#             */
/*   Updated: 2024/10/18 12:34:39 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cmd.h"

void	is_quote(char c, bool *in_single_quote, bool *in_double_quote)
{
	if (c == ('\'' * -1))
	{
		*in_single_quote = !(*in_single_quote);
	}
	else if (c == ('\"' * -1))
	{
		*in_double_quote = !(*in_double_quote);
	}
}

int	process_char(char c, bool *in_word, bool in_single_quote,
		bool in_double_quote)
{
	if (!in_single_quote && !in_double_quote && isspace(c))
	{
		if (*in_word)
		{
			*in_word = false;
		}
	}
	else
	{
		if (!*in_word)
		{
			*in_word = true;
			return (1);
		}
	}
	return (0);
}

int	count_word(const char *str)
{
	int		count;
	bool	in_word;
	bool	in_single_quote;
	bool	in_double_quote;

	count = 0;
	in_word = false;
	in_single_quote = false;
	in_double_quote = false;
	while (*str)
	{
		is_quote(*str, &in_single_quote, &in_double_quote);
		count += process_char(*str, &in_word, in_single_quote, in_double_quote);
		str++;
	}
	return (count);
}

void	check_argv(char ***argv, char **new_argv)
{
	if (new_argv != NULL)
	{
		ft_free_tab((*argv));
		(*argv) = new_argv;
	}
}

void	trim_argv(char ***argv)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*argv)[i])
	{
		tmp = ft_strtrim((*argv)[i], " ");
		free((*argv)[i]);
		(*argv)[i] = tmp;
		i++;
	}
}
