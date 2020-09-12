/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 15:36:18 by frameton          #+#    #+#             */
/*   Updated: 2020/03/02 23:02:32 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*dest;
	char	*sa;
	int		c;

	sa = NULL;
	c = 0;
	if (s)
	{
		if ((dest = ft_strnew(ft_strlen((char *)s))) == NULL)
			return (0);
		sa = dest;
		while (*s)
			*dest++ = f(c++, *s++);
		*dest = '\0';
	}
	return (sa);
}
