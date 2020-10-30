#include "ft_ssl.h"
#include "ft_md5.h"

t_uint32	func0(t_uint32 v[])
{
	return ( v[1] & v[2]) | (~v[1] & v[3]);
}

t_uint32	func1(t_uint32 v[])
{
	return ( v[3] & v[1]) | (~v[3] & v[2]);
}

t_uint32	func2(t_uint32 v[])
{
	return  v[1] ^ v[2] ^ v[3];
}

t_uint32	func3(t_uint32 v[])
{
	return v[2] ^ (v[1] | ~v[3]);
}

t_uint32	rol32(t_uint32 v, t_uint16 n)
{
	t_uint32	mask;

	mask = (1 << n) - 1;
	return ((v >> (32 - n)) & mask) | ((v << n) & ~mask);
}

