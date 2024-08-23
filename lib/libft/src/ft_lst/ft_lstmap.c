/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:16:37 by aditer            #+#    #+#             */
/*   Updated: 2024/03/18 14:12:43 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*dst;
	t_list	*new;

	dst = NULL;
	if (f && del)
	{
		while (lst)
		{
			new = malloc(sizeof(t_list));
			if (!new)
			{
				ft_lstclear(&dst, del);
				return (NULL);
			}
			new->content = f(lst->content);
			new->next = NULL;
			if (!dst)
				dst = new;
			else
				ft_lstadd_back(&dst, new);
			lst = lst->next;
		}
	}
	return (dst);
}
