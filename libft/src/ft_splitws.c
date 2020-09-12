/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitws.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 00:22:19 by frameton          #+#    #+#             */
/*   Updated: 2020/03/02 23:02:32 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_create(size_t *z, char ***tab, const char *s)
{
	*tab = NULL;
	*z = ft_nbword((char *)s);
	return (0);
}

static int	ft_create1(const char **s, const char *s1)
{
	*s = ft_pfrontws((char *)s1);
	return (0);
}

char		**ft_splitws(char const *s)
{
	char	**tab;
	int		i;
	int		i1;
	size_t	z;

	if (!(i1 = ft_create(&z, &tab, s)) && s)
	{
		tab = (char**)ft_malloc_exit(sizeof(*tab)
						* (ft_nbword((char *)s) + 1));
		while (z--)
		{
			i = ft_create1(&s, s);
			while (!(check_whitespaces(s[i])) && s[i])
				i++;
			tab[i1] = (char*)ft_malloc_exit(sizeof(**tab) * (i + 1));
			i = 0;
			while (!(check_whitespaces(*s)) && *s)
				tab[i1][i++] = *s++;
			tab[i1++][i] = '\0';
		}
		tab[i1] = 0;
	}
	return (tab);
}
