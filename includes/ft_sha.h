#ifndef FT_MD5_H
# define FT_MD5_H

/* Context state constants */
# define STATE1	0x6A09E667
# define STATE2	0xBB67AE85
# define STATE3	0x3C6EF372
# define STATE4	0xA54FF53A
# define STATE5	0x510E527F
# define STATE6	0x9B05688C
# define STATE7	0x1F83D9AB
# define STATE8	0x5BE0CD19

typedef unsigned char	t_uint8;
typedef unsigned short	t_uint16;
typedef unsigned int	t_uint32;
typedef unsigned long	t_uint64;

/* md5 context */
typedef struct {
	t_uint32		state[4];                                   /* state (ABCD) */
	t_uint32 		count[2];        /* number of bits, modulo 2^64 (lsb first) */
	unsigned char	buffer[64];                         /* input buffer */
} t_sha256_ctx;

/* operation.c */
t_uint32    ch(t_uint32 x, t_uint32 y, t_uint32 z);
t_uint32    maj(t_uint32 x, t_uint32 y, t_uint32 z);
t_uint32    up_sig0(t_uint32 x);
t_uint32    up_sig1(t_uint32 x);
t_uint32    low_sig0(t_uint32 x);
t_uint32    low_sig1(t_uint32 x);

#endif
