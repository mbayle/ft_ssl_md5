#ifndef FT_SSL_H
# define FT_SSL_H

# define	TRUE	1
# define	FALSE	0

# define	OPT_CHARSET	"pqrso"

typedef	unsigned char	t_uint8;
typedef	unsigned short	t_uint16;
typedef	unsigned int	t_uint32;
typedef	unsigned long	t_uint64;

typedef struct	s_opts {
	t_uint8		p : 1;
	t_uint8		q : 1;
	t_uint8		r : 1;
	t_uint8		s : 1;
	t_uint8		o : 1;
}				t_opts;

#endif
