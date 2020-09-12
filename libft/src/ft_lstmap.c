/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 06:37:56 by frameton          #+#    #+#             */
/*   Updated: 2020/03/02 23:02:32 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define CS content_size

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*new;
	t_list		*bnew;
	t_list		*temp;

	bnew = NULL;
	if (lst)
	{
		temp = f(lst);
		if ((new = ft_lstnew(temp->content, temp->CS)) == NULL)
			return (0);
		bnew = new;
		lst = lst->next;
		while (lst)
		{
			temp = f(lst);
			if ((new->next = ft_lstnew(temp->content, temp->CS)) == NULL)
				return (0);
			new = new->next;
			lst = lst->next;
		}
	}
	return (bnew);
}
