/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 01:20:26 by slegros           #+#    #+#             */
/*   Updated: 2017/11/14 02:26:26 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*begin;
	t_list	*tmp;

	if (lst)
	{
		tmp = f(lst);
		if (!(new = ft_lstnew(tmp->content, tmp->content_size)))
			return (NULL);
		lst = lst->next;
		begin = new;
		while (lst != NULL)
		{
			tmp = f(lst);
			if (!(new->next = ft_lstnew(tmp->content, tmp->content_size)))
				return (NULL);
			lst = lst->next;
			new = new->next;
		}
		return (begin);
	}
	return (lst);
}
