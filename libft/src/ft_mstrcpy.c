/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mstrcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 23:46:38 by frameton          #+#    #+#             */
/*   Updated: 2020/03/02 23:02:32 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_mstrcpy(char *dest, const char *src)
{
	char	*sa;
	int		c;

	c = 0;
	while (src[c])
		c++;
	dest = (char*)ft_malloc_exit(sizeof(*dest) * (c + 1));
	sa = dest;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (sa);
}
