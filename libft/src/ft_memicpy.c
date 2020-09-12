/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memicpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 15:23:37 by frameton          #+#    #+#             */
/*   Updated: 2020/03/02 23:02:32 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memicpy(void *dst, const void *src, size_t n)
{
	int				i;
	int				c;
	unsigned char	*dest;
	unsigned char	*srce;

	i = 0;
	c = 0;
	dest = (unsigned char *)dst;
	srce = (unsigned char *)src;
	while (n-- > 0)
		dest[n] = srce[n];
	return ((void *)dest);
}
