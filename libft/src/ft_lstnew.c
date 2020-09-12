/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 16:09:08 by frameton          #+#    #+#             */
/*   Updated: 2020/03/02 23:02:32 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list		*dst;

	dst = ft_malloc_exit(sizeof(*dst));
	if (content)
	{
		dst->content = ft_memalloc(content_size);
		dst->content = ft_memcpy(dst->content,
				(const void *)content, content_size);
		dst->content_size = content_size;
	}
	else
	{
		dst->content = NULL;
		dst->content_size = 0;
	}
	dst->next = NULL;
	return (dst);
}
