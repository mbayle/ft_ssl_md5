#include "ft_ssl.h"
#include "ft_sha.h"
#include "ft_whirlpool.h"

t_uint32	bswap_32(t_uint32 x)
{
	x = ((x << 8) & 0xFF00FF00u) | ((x >> 8) & 0x00FF00FFu);
	return (x >> 16) | (x << 16);
}

t_uint64	bswap_64(t_uint64 x)
{
	union {
		t_uint64 ll;
		t_uint32 l[2];
	} w, r;
	w.ll = x;
	r.l[0] = bswap_32(w.l[1]);
	r.l[1] = bswap_32(w.l[0]);
	return r.ll;
}

void		swap_str_to_u64(void* to, int index, const void* from, size_t length)
{
	if ( 0 == (( (int)((char*)to - (char*)0) | ((char*)from - (char*)0) | index | length ) & 7) )
	{
		const t_uint64* src = (const t_uint64*)from;
		const t_uint64* end = (const t_uint64*)((const char*)src + length);
		t_uint64* dst = (t_uint64*)((char*)to + index);
		while (src < end)
			*(dst++) = bswap_64(*(src++));
	}
	else
	{
		const char* src = (const char*)from;
		for (length += index; (size_t)index < length; index++) ((char*)to)[index ^ 7] = *(src++);
	}
}
