#ifndef FT_WHIRLPOOL_H
# define FT_WHIRLPOOL_H
# include <stddef.h>

typedef unsigned char	t_uint8;
typedef unsigned short	t_uint16;
typedef unsigned int	t_uint32;
typedef unsigned long	t_uint64;

#define BLOCK_SIZE			64
#define I64(x)				x##ULL
#define IS_ALIGNED_64(p)	(0 == (7 & ((const char*)(p) - (const char*)0)))

#define WHIRLPOOL_OP(src, shift) ( \
		g_whirlpool_sbox[0][(int)(src[ shift      & 7] >> 56)       ] ^ \
		g_whirlpool_sbox[1][(int)(src[(shift + 7) & 7] >> 48) & 0xff] ^ \
		g_whirlpool_sbox[2][(int)(src[(shift + 6) & 7] >> 40) & 0xff] ^ \
		g_whirlpool_sbox[3][(int)(src[(shift + 5) & 7] >> 32) & 0xff] ^ \
		g_whirlpool_sbox[4][(int)(src[(shift + 4) & 7] >> 24) & 0xff] ^ \
		g_whirlpool_sbox[5][(int)(src[(shift + 3) & 7] >> 16) & 0xff] ^ \
		g_whirlpool_sbox[6][(int)(src[(shift + 2) & 7] >>  8) & 0xff] ^ \
		g_whirlpool_sbox[7][(int)(src[(shift + 1) & 7]      ) & 0xff])

typedef union	whirlpool
{
	t_uint64	word;
	t_uint8		byte[8];
}				u_whirlpool;

typedef struct whirlpool_ctx
{
	t_uint64		hash[8];
	t_uint8			message[BLOCK_SIZE];
	t_uint64		length;
} t_whirlpool_ctx;

char    	*whirlpool(const char *msg, t_uint32 len);

#endif
