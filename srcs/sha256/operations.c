#include "ft_ssl.h"
#include "ft_sha.h"
            
static t_uint32    ror32(t_uint32 v, t_uint16 n)
{
    return (((v) >> (n)) | ((v) << (32-(n))));
}

t_uint32    ch(t_uint32 x, t_uint32 y, t_uint32 z)
{
    return ((x & y) ^ (~x & z));
}

t_uint32    maj(t_uint32 x, t_uint32 y, t_uint32 z)
{
    return ((x & y) ^ (x & z) ^ (y & z)); 
}

t_uint32    up_sig0(t_uint32 x)
{
    return (ror32(x, 2) ^ ror32(x, 13) ^ ror32(x, 22));
}

t_uint32    up_sig1(t_uint32 x)
{
    return (ror32(x, 6) ^ ror32(x, 11) ^ ror32(x, 25));
}

t_uint32    low_sig0(t_uint32 x)
{
    return (ror32(x, 7) ^ ror32(x, 18) ^ (x >> 3));
}

t_uint32    low_sig1(t_uint32 x)
{
    return (ror32(x, 17) ^ ror32(x, 19) ^ (x >> 10));
}
