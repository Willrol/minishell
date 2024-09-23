/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:56:55 by aditer            #+#    #+#             */
/*   Updated: 2024/09/23 13:37:43 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
