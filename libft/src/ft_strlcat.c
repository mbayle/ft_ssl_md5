/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 15:23:30 by frameton          #+#    #+#             */
/*   Updated: 2020/03/02 23:02:32 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	sd;
	size_t	ss;
	size_t	c;

	sd = 0;
	ss = 0;
	c = 0;
	while (dst[sd])
		sd++;
	while (src[ss])
		ss++;
	while (src[c] && (sd + c) < (dstsize - 1))
	{
		if (dstsize == 0)
			break ;
		dst[sd + c] = src[c];
		c++;
	}
	dst[sd + c] = '\0';
	if (sd < dstsize)
		return (ss + sd);
	return (ss + dstsize);
}
