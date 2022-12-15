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

char	*ft_strcat(char *s1, const char *s2)
{
	int c;
	int i;

	c = 0;
	i = 0;
	while (s1[i])
		i++;
	while (s2[c])
		s1[i++] = s2[c++];
	s1[i] = '\0';
	return (s1);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int				i;
	unsigned char	*dest;
	unsigned char	*srce;

	i = 0;
	dest = (unsigned char *)dst;
	srce = (unsigned char *)src;
	while (n-- > 0)
		dest[i++] = *srce++;
	return ((void *)dest);
}

size_t		ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	if(!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

void	*ft_memset(void *b, int c, size_t len)
{
	int				i;
	unsigned char	*b1;

	i = 0;
	b1 = (unsigned char *)b;
	while (len-- > 0)
		b1[i++] = c;
	return ((void *)b1);
}