/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:43:40 by aditer            #+#    #+#             */
/*   Updated: 2024/09/18 16:28:33 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_str_replace(char *str, char *old, char *new)
// {
// 	const int	old_len = ft_strlen(old);
// 	const int	new_len = ft_strlen(new);
// 	const int	result_len = ft_strlen(str) + (new_len - old_len);
// 	char		*result;
// 	char		*tmp;

// 	result = ft_calloc(result_len + 1, sizeof(char));
// 	if (!result)
// 		return (NULL);
// 	tmp = result;
// 	while (*str)
// 	{
// 		if (ft_strnstr(str, old, ft_strlen(old)) != NULL)
// 		{
// 			ft_strlcpy(tmp, new, new_len + 1);
// 			tmp += new_len;
// 			str += old_len;
// 		}
// 		else
// 		{
// 			*tmp++ = *str++;
// 		}
// 	}
// 	return (result);
// }

static char	*allocate_new_str(size_t old_len, size_t old_sub_len,
		size_t new_sub_len)
{
	size_t	new_len;
	char	*new_str;

	new_len = old_len + (new_sub_len - old_sub_len) + 1;
	new_str = ft_calloc(new_len, sizeof(char *));
	if (!new_str)
		return (NULL);
	return (new_str);
}

static void	copy_and_replace(char *dest, const char *src, const char *old_sub,
		const char *new_sub)
{
	const char	*temp;
	size_t		segment_len;
	size_t		old_sub_len;
	size_t		new_sub_len;

	old_sub_len = ft_strlen(old_sub);
	new_sub_len = ft_strlen(new_sub);
	temp = src;
	temp = ft_strnstr(temp, old_sub, ft_strlen(temp));
	if (temp != NULL)
	{
		segment_len = temp - src;
		ft_memcpy(dest, src, segment_len);
		dest += segment_len;
		ft_memcpy(dest, new_sub, new_sub_len);
		dest += new_sub_len;
		temp += old_sub_len;
		src = temp;
	}
	ft_strlcpy(dest, src, ft_strlen(src) + 1);
}

char	*ft_str_replace(char *str, char *old_sub, char *new_sub)
{
	char	*new_str;
	size_t	old_len;
	size_t	old_sub_len;
	size_t	new_sub_len;

	if (!str || !old_sub || !new_sub)
		return (NULL);
	old_len = ft_strlen(str);
	old_sub_len = ft_strlen(old_sub);
	new_sub_len = ft_strlen(new_sub);
	new_str = allocate_new_str(old_len, old_sub_len, new_sub_len);
	if (!new_str)
		return (NULL);
	copy_and_replace(new_str, str, old_sub, new_sub);
	free(str);
	return (new_str);
}
