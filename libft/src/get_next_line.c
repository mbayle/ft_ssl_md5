/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 00:22:23 by mabayle           #+#    #+#             */
/*   Updated: 2018/09/12 01:17:55 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_free(void **ap)
{
	if (ap == NULL)
		return ;
	free(*ap);
	*ap = NULL;
}

static int			ft_check(char **buff, char **line)
{
	char			*tmp;

	tmp = ft_strchr(*buff, SEPARATOR);
	if (tmp)
	{
		*line = ft_strsub(*buff, 0, tmp - *buff);
		ft_memmove(*buff, tmp + 1, ft_strlen(tmp));
		tmp = NULL;
		return (1);
	}
	return (0);
}

static	void		ft_add_data(char **buff, char *tmp, char *new_buff)
{
	tmp = ft_strdup(*buff);
	ft_free((void **)buff);
	*buff = ft_strjoin(tmp, new_buff);
	ft_free((void **)&tmp);
}

static	int			ft_fill(int fd, char **buff, char **line)
{
	char			*new_buff;
	char			*tmp;
	int				ret;

	new_buff = (char *)ft_malloc_exit(sizeof(char) * BUFF_SIZE + 1);
	new_buff[BUFF_SIZE] = 0;
	while ((ret = read(fd, new_buff, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		new_buff[ret] = '\0';
		tmp = NULL;
		if (*buff)
			ft_add_data(buff, tmp, new_buff);
		else
			*buff = ft_strdup(new_buff);
		if (ft_check(buff, line))
		{
			ft_free((void **)&new_buff);
			return (1);
		}
	}
	ft_free((void **)&new_buff);
	return (0);
}

int					get_next_line(int fd, char **line)
{
	static char		*buff[_SC_OPEN_MAX];
	char			*fd_error;
	int				ret;

	fd_error = (char *)ft_malloc_exit(sizeof(char) * 1);
	if (!line || fd < 0 || fd > _SC_OPEN_MAX || read(fd, fd_error, 0) < 0)
	{
		ft_free((void **)&fd_error);
		if (line != NULL)
			*line = NULL;
		return (-1);
	}
	ft_free((void **)&fd_error);
	if (buff[fd] && ft_check(&buff[fd], line))
		return (1);
	if ((ret = ft_fill(fd, &buff[fd], line)) != 0)
		return (ret);
	if (buff[fd] == NULL || buff[fd][0] == '\0')
		return (0);
	*line = buff[fd];
	buff[fd] = NULL;
	return (1);
}
