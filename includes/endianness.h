#ifndef FT_ENDIANNESS_H
# define FT_ENDIANNESS_H
# include <stddef.h>

typedef	unsigned int	t_uint32;
typedef	unsigned long	t_uint64;

#if IS_BIG_ENDIAN
# define be2me_32(x) (x)
# define be2me_64(x) (x)
# define le2me_32(x) bswap_32(x)
# define le2me_64(x) bswap_64(x)

# define be32_copy(to, index, from, length) memcpy((char*)(to) + (index), (from), (length))
# define le32_copy(to, index, from, length) swap_str_to_t_uint32((to), (index), (from), (length))
# define be64_copy(to, index, from, length) memcpy((char*)(to) + (index), (from), (length))
# define le64_copy(to, index, from, length) swap_str_to_u64((to), (index), (from), (length))
# define me64_to_be_str(to, from, length) memcpy((to), (from), (length))
# define me64_to_le_str(to, from, length) swap_u64_to_str((to), (from), (length))
#else /* IS_BIG_ENDIAN */
# define be2me_32(x) bswap_32(x)
# define be2me_64(x) bswap_64(x)
# define le2me_32(x) (x)
# define le2me_64(x) (x)

# define be32_copy(to, index, from, length) swap_str_to_t_uint32((to), (index), (from), (length))
# define le32_copy(to, index, from, length) memcpy((char*)(to) + (index), (from), (length))
# define be64_copy(to, index, from, length) swap_str_to_u64((to), (index), (from), (length))
# define le64_copy(to, index, from, length) memcpy((char*)(to) + (index), (from), (length))
# define me64_to_be_str(to, from, length) swap_u64_to_str((to), (from), (length))
# define me64_to_le_str(to, from, length) memcpy((to), (from), (length))
#endif /* IS_BIG_ENDIAN */

#if __BYTE_ORDER == __LITTLE_ENDIAN
# define SWAP32(n) (bswap_32(n))
# define SWAP64(n) (bswap_64(n))
#else
# define SWAP32(n) (n)
# define SWAP64(n) (n)
#endif

t_uint32	bswap_32(t_uint32 x);
t_uint64	bswap_64(t_uint64 x);

void		swap_str_to_u64(void* to, int index, const void* from, size_t length);

#endif //FT_ENDIANNESS_H
