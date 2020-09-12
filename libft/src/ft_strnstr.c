/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 15:21:51 by frameton          #+#    #+#             */
/*   Updated: 2020/03/02 23:02:32 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*i;
	const char	*c;
	size_t		j;

	if (!(*needle))
		return ((char *)haystack);
	while (len-- && *haystack)
	{
		if (*haystack == *needle)
		{
			i = haystack++;
			c = needle++;
			j = len;
			while (j-- && *haystack && *needle && (*haystack++ == *needle))
				needle++;
			haystack = i;
			if (*needle == '\0')
				return ((char *)i);
			needle = c;
		}
		haystack++;
	}
	return (NULL);
}
