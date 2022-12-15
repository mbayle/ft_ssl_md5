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

void sha256_transform(t_sha256_context *context, const t_uint8 data[])
{
	t_uint32 a, b, c, d, e, f, g, h, i, j, t1, t2, m[64];

	for (i = 0, j = 0; i < 16; ++i, j += 4)
		m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);
	for ( ; i < 64; ++i)
		m[i] = low_sig1(m[i - 2]) + m[i - 7] + low_sig0(m[i - 15]) + m[i - 16];

	a = context->state[0];
	b = context->state[1];
	c = context->state[2];
	d = context->state[3];
	e = context->state[4];
	f = context->state[5];
	g = context->state[6];
	h = context->state[7];

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

	context->state[0] += a;
	context->state[1] += b;
	context->state[2] += c;
	context->state[3] += d;
	context->state[4] += e;
	context->state[5] += f;
	context->state[6] += g;
	context->state[7] += h;
}

void sha256_update(t_sha256_context *context, const t_uint8 data[], size_t len)
{
	t_uint32 i;

	for (i = 0; i < len; ++i) {
		context->buffer[context->datalen] = data[i];
		context->datalen++;
		if (context->datalen == 64) {
			sha256_transform(context, context->buffer);
			context->bitlen += 512;
			context->datalen = 0;
		}
	}
}

void sha256_final(t_sha256_context *context, t_uint8 hash[])
{
	t_uint32 i;

	i = context->datalen;

	if (context->datalen < 56) {
		context->buffer[i++] = 0x80;
		while (i < 56)
			context->buffer[i++] = 0x00;
	}
	else {
		context->buffer[i++] = 0x80;
		while (i < 64)
			context->buffer[i++] = 0x00;
		sha256_transform(context, context->buffer);
		ft_bzero(context->buffer, 56);
	}

	context->bitlen += context->datalen * 8;
	context->buffer[63] = context->bitlen;
	context->buffer[62] = context->bitlen >> 8;
	context->buffer[61] = context->bitlen >> 16;
	context->buffer[60] = context->bitlen >> 24;
	context->buffer[59] = context->bitlen >> 32;
	context->buffer[58] = context->bitlen >> 40;
	context->buffer[57] = context->bitlen >> 48;
	context->buffer[56] = context->bitlen >> 56;
	sha256_transform(context, context->buffer);

	for (i = 0; i < 4; ++i) {
		hash[i]      = (context->state[0] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 4]  = (context->state[1] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 8]  = (context->state[2] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 12] = (context->state[3] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 16] = (context->state[4] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 20] = (context->state[5] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 24] = (context->state[6] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 28] = (context->state[7] >> (24 - i * 8)) & 0x000000ff;
	}
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

static void sha256_init(t_sha256_context *context)
{
	context->datalen = 0;
	context->bitlen = 0;
	context->state[0] = SHA256_STATE1;
	context->state[1] = SHA256_STATE2;
	context->state[2] = SHA256_STATE3;
	context->state[3] = SHA256_STATE4;
	context->state[4] = SHA256_STATE5;
	context->state[5] = SHA256_STATE6;
	context->state[6] = SHA256_STATE7;
	context->state[7] = SHA256_STATE8;
}

char    *sha256(const char *msg, t_uint32 len)
{
    static t_sha256_context    *context = NULL;
    t_uint8                digest[36];
    char                   *hash;

	hash = NULL;
    if (context == NULL)
    {
        if (!(context = malloc(sizeof(t_sha256_context))))
            return (NULL);
		sha256_init(context);
    }
    sha256_update(context, (t_uint8 *)msg , len);
    if (len < 64)
	{
        sha256_final(context, (t_uint8 *)digest);
		hash = generate_hash((t_uint8 *)digest);
        free(context);
		context = NULL;
	}
    return (hash);
}