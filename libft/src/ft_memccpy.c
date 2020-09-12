/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 15:07:40 by frameton          #+#    #+#             */
/*   Updated: 2020/03/02 23:02:32 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char *dest;
	unsigned char *srce;

	dest = (unsigned char *)dst;
	srce = (unsigned char *)src;
	while (n-- > 0)
	{
		if (*srce != (unsigned char)c)
			*dest++ = *srce++;
		else
		{
			*dest++ = (unsigned char)c;
			return ((void *)dest);
		}
	}
	return (NULL);
}
