#ifndef FT_SSL_H
# define FT_SSL_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define FAILURE	1
# define SUCCESS	0

# define TRUE	1
# define FALSE	0

# define OPT_CHARSET	"pqrso"

/*
** Defining cipher values
*/

typedef enum		e_cipher {
	MD5,
	SHA256,
	WHIRLPOOL,
    NB_OF_CIPHERS,
    ERROR,
}                   t_cipher;

/*
** Defining error codes
*/

# define ERR_NO_ARGS	-1
# define ERR_BAD_CIPHER	-2
# define ERR_BAD_OPTION	-3
# define ERR_NO_MEM		-4
# define ERR_OPEN       -5

/*
** Defining custom types
*/

typedef	unsigned char	t_uint8;
typedef	unsigned short	t_uint16;
typedef	unsigned int	t_uint32;
typedef	unsigned long	t_uint64;

typedef char *(*hash_fn)(const char *msg, t_uint32 len);

typedef struct	s_opt {
	t_uint8		p : 1;
	t_uint8		q : 1;
	t_uint8		r : 1;
	t_uint8		s : 1;
	t_uint8		o : 1;
	t_uint8		err : 1;
}				t_opt;

/*
** hash.c functions
*/
char        hash_message(const t_cipher cipher, const t_opt options, char **args, int count);

/*
** misc functions
*/
void		ft_bzero(void *s, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strchr(const char *s, int c);
char    	*ft_strcat(char *s1, const char *s2);
void	    *ft_memcpy(void *dst, const void *src, size_t n);

/*
** display functions
*/
void    display_hash(char *hash, const t_opt options, const t_cipher cipher, char *args);

/*
** help.c function
*/
void		print_usage(void);
#endif
