/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_str_to_board.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 18:23:45 by mabayle           #+#    #+#             */
/*   Updated: 2019/03/22 16:32:11 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_create(int size_y, char **tab, char *str)
{
	tab = (char **)ft_malloc_exit(sizeof(char *) * (size_y + 1));
	tab[0] = ft_strdup(str);
	tab[1] = NULL;
	return (tab);
}

static char	**ft_new(int size_y, char **tab, char *str)
{
	char	**t;
	int		i;

	i = -1;
	t = (char **)ft_malloc_exit(sizeof(char *) * (size_y + 1));
	t[size_y] = NULL;
	while (tab[++i])
		t[i] = ft_strdup(tab[i]);
	t[i] = ft_strdup(str);
	i = -1;
	while (tab[++i])
		ft_strdel(&tab[i]);
	ft_strdel(&tab[i]);
	free(tab);
	tab = NULL;
	return (t);
}

char		**ft_add_str_to_board(char **tab, char *str)
{
	int size_y;

	if (!str)
		return (NULL);
	if (!tab)
	{
		if ((tab = ft_create(1, tab, str)) == NULL)
			return (NULL);
	}
	else
	{
		size_y = 0;
		while (tab[size_y])
			size_y++;
		if ((tab = ft_new(size_y + 1, tab, str)) == NULL)
			return (NULL);
	}
	return (tab);
}
