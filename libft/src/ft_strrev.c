/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 03:06:53 by mabayle           #+#    #+#             */
/*   Updated: 2020/01/24 03:13:53 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrev(char *str)
{
	unsigned int	i;
	unsigned int	j;
	char			temp;

	if (str)
	{
		j = 0;
		while (str[j] != '\0')
		{
			j++;
		}
		j--;
		i = 0;
		while (i < j)
		{
			temp = str[i];
			str[i] = str[j];
			str[j] = temp;
			i++;
			j--;
		}
	}
	return (str);
}
