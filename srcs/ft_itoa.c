/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 15:23:03 by frameton          #+#    #+#             */
/*   Updated: 2020/03/02 23:02:32 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	long int	nb;
	char		*dest;
	char		*sa;

	nb = n;
	if ((dest = ft_strnew(ft_nci((int)n))) == NULL)
		return (0);
	sa = dest;
	if (nb < 0)
	{
		*dest++ = '-';
		nb = nb * -1;
	}
	while (nb / 10)
	{
		*dest++ = ((nb % 10) + 48);
		nb = nb / 10;
	}
	*dest++ = nb + 48;
	dest = sa;
	if (dest[0] == '-')
		dest++;
	ft_strev(dest);
	return (sa);
}
