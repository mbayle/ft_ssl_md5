#ifndef FT_SSL_H
# define FT_SSL_H

# include <unistd.h>
# include <stdlib.h>

# define FAILURE	1
# define SUCCESS	0

# define TRUE	1
# define FALSE	0

# define OPT_CHARSET	"pqrso"

/*
** Defining cipher values
*/

enum		e_cipher {
	MD5,
	SHA256,
};

/*
** Defining error codes
*/

# define ERR_NO_ARGS	-1
# define ERR_BAD_CIPHER	-2
# define ERR_BAD_OPTION	-3
# define ERR_NO_MEM		-4

/*
** Defining custom types
*/

typedef	unsigned char	t_uint8;
typedef	unsigned short	t_uint16;
typedef	unsigned int	t_uint32;
typedef	unsigned long	t_uint64;

typedef struct	s_opt {
	t_uint8		p : 1;
	t_uint8		q : 1;
	t_uint8		r : 1;
	t_uint8		s : 1;
	t_uint8		o : 1;
}				t_opt;

/*
** misc functions
*/

void		print_usage(void);
void		ft_bzero(void *s, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strchr(const char *s, int c);

#endif
