#include "ft_ssl.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (*str)
	{
		if (*str == (unsigned char)c)
			return ((void *)str);
		str++;
	}
	if ((unsigned char)c == '\0')
		return ((void *)str);
	return (0);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (-1);
	while ((*s1 == *s2) && (*s1 && *s2++))
		s1++;
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char *s1;

	s1 = (unsigned char *)s;
	while (n-- > 0)
		*s1++ = 0;
}

void	print_usage(void)
{
	write(1, "usage: ft_ssl [cipher] [-pqro] [-s string] [files ...]\n", 55);
}
