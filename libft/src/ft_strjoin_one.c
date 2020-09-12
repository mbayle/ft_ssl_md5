/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 06:44:58 by mabayle           #+#    #+#             */
/*   Updated: 2020/03/12 05:24:00 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_one(char *s1, char c)
{
	int		i;
	int		len;
	char	*result;

	if (!s1 && !c)
		return (NULL);
	if (!s1)
	{
		result = ft_strnew(1);
		result[0] = c;
	}
	else if (!c)
		return (s1);
	else
	{
		i = -1;
		len = ft_strlen(s1);
		result = ft_strnew(len + 1);
		while (++i < len)
			result[i] = s1[i];
		result[i] = c;
	}
	return (result);
}
