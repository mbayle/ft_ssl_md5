/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 15:35:24 by frameton          #+#    #+#             */
/*   Updated: 2020/03/02 23:02:32 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	char	*sa;

	sa = NULL;
	if (s1 && s2)
	{
		if ((dest = ft_strnew((ft_strlen((char *)s1) + ft_strlen((char *)s2))))
		== NULL)
			return (NULL);
		sa = dest;
		dest = ft_strcpy(dest, s1);
		dest = ft_pstrback(dest);
		dest++;
		dest = ft_strcpy(dest, s2);
	}
	return (sa);
}
