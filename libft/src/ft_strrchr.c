/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 15:23:15 by frameton          #+#    #+#             */
/*   Updated: 2020/03/02 23:02:32 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*str;
	unsigned char	*i;

	str = (unsigned char *)s;
	i = str;
	str = (unsigned char *)ft_pstrback((char *)str);
	if ((unsigned char)c == '\0' && *str)
	{
		str++;
		return ((char *)str);
	}
	while (str >= i)
	{
		if (*str == (unsigned char)c)
			return ((char *)str);
		str--;
	}
	return (0);
}
