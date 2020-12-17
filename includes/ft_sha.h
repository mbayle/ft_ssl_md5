#ifndef FT_SHA256_H
# define FT_SHA256_H

/* Context state constants */
# define SHA256_STATE1	0x6A09E667
# define SHA256_STATE2	0xBB67AE85
# define SHA256_STATE3	0x3C6EF372
# define SHA256_STATE4	0xA54FF53A
# define SHA256_STATE5	0x510E527F
# define SHA256_STATE6	0x9B05688C
# define SHA256_STATE7	0x1F83D9AB
# define SHA256_STATE8	0x5BE0CD19

typedef unsigned char	t_uint8;
typedef unsigned short	t_uint16;
typedef unsigned int	t_uint32;
typedef unsigned long	t_uint64;

/* md5 context */
typedef struct {
	t_uint32		state[8];
	t_uint8			buffer[64];
	t_uint32		datalen;
	t_uint64		bitlen;
} t_sha256_ctx;

typedef union	shaunion
{
	t_uint32		word;
	t_uint8			byte[4];
}				u_sha256;

/* operation.c */
t_uint32    ch(t_uint32 x, t_uint32 y, t_uint32 z);
t_uint32    maj(t_uint32 x, t_uint32 y, t_uint32 z);
t_uint32    up_sig0(t_uint32 x);
t_uint32    up_sig1(t_uint32 x);
t_uint32    low_sig0(t_uint32 x);
t_uint32    low_sig1(t_uint32 x);

/* init_sha256.c */
void    sha256_init(t_sha256_ctx *ctx);
char    *sha256(const char *msg, t_uint32 len);

#endif
