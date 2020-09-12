/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 19:57:42 by frameton          #+#    #+#             */
/*   Updated: 2020/03/06 02:55:56 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		c;
	char	*s2;

	c = 0;
	if (!s1)
		return (NULL);
	while (s1[c])
		c++;
	if ((s2 = ft_strnew(c)) == NULL)
		return (0);
	c = 0;
	while (s1[c])
	{
		s2[c] = s1[c];
		c++;
	}
	return (s2);
}
