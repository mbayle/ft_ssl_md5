/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 23:50:43 by frameton          #+#    #+#             */
/*   Updated: 2020/03/02 23:02:32 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_sstrev(char **s, int c)
{
	int		d;
	int		f;
	char	*tmp;

	d = c;
	f = c;
	tmp = NULL;
	if (!(s[c]))
		return (s);
	while (s[f])
		f++;
	f--;
	while (d < f)
	{
		tmp = s[d];
		s[d] = s[f];
		s[f] = tmp;
		d++;
		f--;
	}
	return (s);
}
