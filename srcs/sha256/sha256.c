#include "ft_ssl.h"
#include "ft_sha.h"

static const unsigned k[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

#include <stdio.h>
static void		print_states(t_sha256_ctx *ctx, t_uint8 depth)
{
	while (depth--)
		printf("\t");
	printf("Current states: %#x:%#x:%#x:%#x:%#x:%#x:%#x:%#x\n", ctx->state[0],
	ctx->state[1],
	ctx->state[2],
	ctx->state[3],
	ctx->state[4],
	ctx->state[5],
	ctx->state[6],
	ctx->state[7]);
}

void sha256_transform(t_sha256_ctx *ctx, const t_uint8 data[])
{
	t_uint32 a, b, c, d, e, f, g, h, i, j, t1, t2, m[64];

	printf("\t\tEntering sha256_transform\n");
	for (i = 0, j = 0; i < 16; ++i, j += 4)
		m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);
	for ( ; i < 64; ++i)
		m[i] = low_sig1(m[i - 2]) + m[i - 7] + low_sig0(m[i - 15]) + m[i - 16];

	a = ctx->state[0];
	b = ctx->state[1];
	c = ctx->state[2];
	d = ctx->state[3];
	e = ctx->state[4];
	f = ctx->state[5];
	g = ctx->state[6];
	h = ctx->state[7];

	for (i = 0; i < 64; ++i) {
		t1 = h + up_sig1(e) + ch(e,f,g) + k[i] + m[i];
		t2 = up_sig0(a) + maj(a,b,c);
		h = g;
		g = f;
		f = e;
		e = d + t1;
		d = c;
		c = b;
		b = a;
		a = t1 + t2;
	}

	ctx->state[0] += a;
	ctx->state[1] += b;
	ctx->state[2] += c;
	ctx->state[3] += d;
	ctx->state[4] += e;
	ctx->state[5] += f;
	ctx->state[6] += g;
	ctx->state[7] += h;
	print_states(ctx, 2);
	printf("\t\tExitting sha256_transform\n");
}

void sha256_update(t_sha256_ctx *ctx, const t_uint8 data[], size_t len)
{
	t_uint32 i;

	printf("\tEntering sha256_update\n");
	for (i = 0; i < len; ++i) {
		ctx->buffer[ctx->datalen] = data[i];
		ctx->datalen++;
		if (ctx->datalen == 64) {
			sha256_transform(ctx, ctx->buffer);
			ctx->bitlen += 512;
			ctx->datalen = 0;
		}
	}
	print_states(ctx, 1);
	printf("\tExitting sha256_update\n\n");
}

void sha256_final(t_sha256_ctx *ctx, t_uint8 hash[])
{
	t_uint32 i;

	printf("\tEntering sha256_final\n");
	i = ctx->datalen;

	if (ctx->datalen < 56) {
		ctx->buffer[i++] = 0x80;
		while (i < 56)
			ctx->buffer[i++] = 0x00;
	}
	else {
		ctx->buffer[i++] = 0x80;
		while (i < 64)
			ctx->buffer[i++] = 0x00;
		sha256_transform(ctx, ctx->buffer);
		ft_bzero(ctx->buffer, 56);
	}

	ctx->bitlen += ctx->datalen * 8;
	ctx->buffer[63] = ctx->bitlen;
	ctx->buffer[62] = ctx->bitlen >> 8;
	ctx->buffer[61] = ctx->bitlen >> 16;
	ctx->buffer[60] = ctx->bitlen >> 24;
	ctx->buffer[59] = ctx->bitlen >> 32;
	ctx->buffer[58] = ctx->bitlen >> 40;
	ctx->buffer[57] = ctx->bitlen >> 48;
	ctx->buffer[56] = ctx->bitlen >> 56;
	sha256_transform(ctx, ctx->buffer);

	for (i = 0; i < 4; ++i) {
		hash[i]      = (ctx->state[0] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 4]  = (ctx->state[1] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 8]  = (ctx->state[2] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 12] = (ctx->state[3] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 16] = (ctx->state[4] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 20] = (ctx->state[5] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 24] = (ctx->state[6] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 28] = (ctx->state[7] >> (24 - i * 8)) & 0x000000ff;
	}
	print_states(ctx, 1);
	printf("\tExitting sha256_final\n");
}

void    shablock(char *str, u_sha256 block)
{
	t_uint8	    i;
	char        j;
	char        n;

	i = 0;
	while (i < 4)
	{
		if (block.byte[i] <= 16)
			str[i * 2] = '0';
		j = 3;
		while (--j)
		{
			n = block.byte[i] % 16;
			if (n <= 9)
				str[i * 2 + (j - 1)] = n + '0';
			else
				str[i * 2 + (j - 1)] = n - 10 + 'a';
			block.byte[i] = block.byte[i] / 16;
		}
		i++;
	}
	str[8] = '\0';
}

char	*generate_hash(t_uint8 *digest)
{
	char 		*hash;
	int			i = 0;
	u_sha256	block;
	char        s[9];

	if (!(hash = malloc(65)))
		return (NULL);
	ft_bzero(hash, 65);

	while (i < 8)
	{
		block.word = ((t_uint32 *)digest)[i];
		ft_bzero(s, 8);
		shablock((char *)s, block);
		ft_strcat(hash, s);
		i++;
	}
	return (hash);
}

char    *sha256(const char *msg, t_uint32 len)
{
    static t_sha256_ctx    *context = NULL;
    t_uint8                digest[36];
    char                   *hash;

    if (context == NULL)
    {
        if (!(context = malloc(sizeof(t_sha256_ctx))))
            return (NULL);
		sha256_init(context);
    }

    sha256_update(context, (t_uint8 *)msg , len);
    if (len < 64)
	{
        sha256_final(context, (t_uint8 *)digest);
        free(context);
	}

	hash = generate_hash((t_uint8 *)digest);
    return (hash);
}
