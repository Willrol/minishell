/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:43:40 by aditer            #+#    #+#             */
/*   Updated: 2024/09/17 14:40:01 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_replace(char *str, char *old, char *new)
{
	const int	old_len = ft_strlen(old);
	const int	new_len = ft_strlen(new);
	const int	result_len = ft_strlen(str) + (new_len - old_len);
	char		*result;
	char		*tmp;

	result = ft_calloc(result_len + 1, sizeof(char));
	if (!result)
		return (NULL);
	tmp = result;
	while (*str)
	{
		if (ft_strnstr(str, old, ft_strlen(old)) != NULL)
		{
			ft_strlcpy(tmp, new, new_len + 1);
			tmp += new_len;
			str += old_len;
		}
		else
		{
			*tmp++ = *str++;
		}
	}
	return (result);
}
