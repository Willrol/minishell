/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:23:32 by aditer            #+#    #+#             */
/*   Updated: 2024/10/22 13:29:37 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cmd.h"

void	check_argv_empty(char **argv)
{
	if (ft_strlen(*argv) == 0)
	{
		free(*argv);
		*argv = NULL;
	}
}

void	rm_argv_null(int *argc, char ***argv)
{
	int		i;
	int		j;
	int		cpt;
	char	**new_argv;

	i = -1;
	j = 0;
	cpt = 0;
	while (++i < (*argc))
		if ((*argv)[i] == NULL)
			cpt++;
	new_argv = ft_calloc((*argc) - cpt + 1, sizeof(char *));
	if (!new_argv)
		return ;
	i = -1;
	while (++i < (*argc))
	{
		if ((*argv)[i] != NULL)
			new_argv[j++] = ft_strdup((*argv)[i]);
	}
	(*argc) = j;
	ft_free_tab(*argv);
	*argv = new_argv;
}
