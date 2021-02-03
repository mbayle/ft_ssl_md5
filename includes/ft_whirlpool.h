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

#if IS_BIG_ENDIAN
# define be2me_32(x) (x)
# define be2me_64(x) (x)
# define le2me_32(x) bswap_32(x)
# define le2me_64(x) bswap_64(x)

# define be32_copy(to, index, from, length) memcpy((char*)(to) + (index), (from), (length))
# define le32_copy(to, index, from, length) swap_str_to_u32((to), (index), (from), (length))
# define be64_copy(to, index, from, length) memcpy((char*)(to) + (index), (from), (length))
# define le64_copy(to, index, from, length) swap_str_to_u64((to), (index), (from), (length))
# define me64_to_be_str(to, from, length) memcpy((to), (from), (length))
# define me64_to_le_str(to, from, length) swap_u64_to_str((to), (from), (length))
#else /* IS_BIG_ENDIAN */
# define be2me_32(x) bswap_32(x)
# define be2me_64(x) bswap_64(x)
# define le2me_32(x) (x)
# define le2me_64(x) (x)

# define be32_copy(to, index, from, length) swap_str_to_u32((to), (index), (from), (length))
# define le32_copy(to, index, from, length) memcpy((char*)(to) + (index), (from), (length))
# define be64_copy(to, index, from, length) swap_str_to_u64((to), (index), (from), (length))
# define le64_copy(to, index, from, length) memcpy((char*)(to) + (index), (from), (length))
# define me64_to_be_str(to, from, length) swap_u64_to_str((to), (from), (length))
# define me64_to_le_str(to, from, length) memcpy((to), (from), (length))
#endif /* IS_BIG_ENDIAN */

#if __BYTE_ORDER == __LITTLE_ENDIAN
# define SWAP32(n) (wswap_uint32(n))
# define SWAP64(n) (wswap_uint64(n))
#else
# define SWAP32(n) (n)
# define SWAP64(n) (n)
#endif

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

t_uint32	bswap_32(t_uint32 x);
t_uint64	bswap_64(t_uint64 x);
void		swap_str_to_u64(void* to, int index, const void* from, size_t length);
char    	*whirlpool(const char *msg, t_uint32 len);

#endif
