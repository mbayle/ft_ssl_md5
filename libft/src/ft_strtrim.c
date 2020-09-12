/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 18:38:41 by frameton          #+#    #+#             */
/*   Updated: 2020/03/02 23:02:32 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*dest;
	char	*sa;
	int		d;
	int		f;

	sa = NULL;
	if (s)
	{
		f = ft_ipbackws((char *)s);
		d = ft_ipfrontws((char *)s);
		if (d > f)
			ft_swap(&d, &f);
		if ((dest = ft_strnew((size_t)((f - d) + 1))) == NULL)
			return (NULL);
		sa = dest;
		while (d <= f)
			*dest++ = s[d++];
	}
	return (sa);
}
