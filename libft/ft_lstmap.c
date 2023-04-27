/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:09:50 by aessakhi          #+#    #+#             */
/*   Updated: 2021/05/20 15:12:57 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	t_list	*nextlink;

	start = NULL;
	while (lst)
	{
		nextlink = ft_lstnew((f)(lst->content));
		if (!nextlink)
		{
			while (start)
			{
				nextlink = start->next;
				(*del)(start->content);
				free(start);
				start = nextlink;
			}
			return (NULL);
		}
		ft_lstadd_back(&start, nextlink);
		lst = lst->next;
	}
	return (start);
}
