#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <fcntl.h>

typedef unsigned char BYTE;             // 8-bit byte
typedef unsigned int  WORD;             // 32-bit word, change to "long" for 16-bit machines
typedef unsigned long DWORD;            // 64-bit word

typedef unsigned long	t_uint64;
typedef unsigned int	t_uint32;
typedef unsigned short	t_uint16;

typedef union	shaunion
{
	DWORD		word;
	BYTE		byte[8];
}				u_sha512;

typedef struct {
	union {
		BYTE data[128];
		DWORD word[16];
	};
	DWORD datalen;
	unsigned long long bitlen;
	union {
		BYTE  digest[64];
		DWORD state[8];
	};
} SHA512_CTX;

t_uint64 swap_uint64(t_uint64 val)
{
	val = ((val << 8) & 0xFF00FF00FF00FF00ULL ) | ((val >> 8) & 0x00FF00FF00FF00FFULL );
	val = ((val << 16) & 0xFFFF0000FFFF0000ULL ) | ((val >> 16) & 0x0000FFFF0000FFFFULL );
	return (val << 32) | (val >> 32);
}

t_uint32 swap_uint32(t_uint32 val)
{
	val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF ); 
	return (val << 16) | (val >> 16);
}

#if __BYTE_ORDER == __LITTLE_ENDIAN
# define SWAP32(n) (swap_uint32(n))
# define SWAP64(n) (swap_uint64(n))
#else
# define SWAP32(n) (n)
# define SWAP64(n) (n)
#endif

#define M(i) m[(i) & 0x0f]

static const t_uint64 k[80] = {
	0x428a2f98d728ae22, 0x7137449123ef65cd,
	0xb5c0fbcfec4d3b2f, 0xb5c0fbcfec4d3b2f,
	0x3956c25bf348b538, 0x59f111f1b605d019,
	0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
	0xd807aa98a3030242, 0x12835b0145706fbe,
	0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
	0x72be5d74f27b896f, 0x80deb1fe3b1696b1,
	0x9bdc06a725c71235, 0xc19bf174cf692694,
	0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
	0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
	0x2de92c6f592b0275, 0x4a7484aa6ea6e483,
	0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
	0x983e5152ee66dfab, 0xa831c66d2db43210,
	0xb00327c898fb213f, 0xbf597fc7beef0ee4,
	0xc6e00bf33da88fc2, 0xd5a79147930aa725,
	0x06ca6351e003826f, 0x142929670a0e6e70,
	0x27b70a8546d22ffc, 0x2e1b21385c26c926,
	0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
	0x650a73548baf63de, 0x766a0abb3c77b2a8,
	0x81c2c92e47edaee6, 0x92722c851482353b,
	0xa2bfe8a14cf10364, 0xa81a664bbc423001,
	0xc24b8b70d0f89791, 0xc76c51a30654be30,
	0xd192e819d6ef5218, 0xd69906245565a910,
	0xf40e35855771202a, 0x106aa07032bbd1b8,
	0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
	0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
	0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
	0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
	0x748f82ee5defb2fc, 0x78a5636f43172f60,
	0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9,
	0xbef9a3f7b2c67915, 0xc67178f2e372532b,
	0xca273eceea26619c, 0xd186b8c721c0c207,
	0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
	0x06f067aa72176fba, 0x0a637dc5a2c898a6,
	0x113f9804bef90dae, 0x1b710b35131c471b,
	0x28db77f523047d84, 0x32caab7b40c72493,
	0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
	0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
	0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};

static void		print_states(SHA512_CTX *ctx, BYTE depth)
{
	while (depth--)
		printf("\t");
	printf("Current states: %#lx:%#lx:%#lx:%#lx:%#lx:%#lx:%#lx:%#lx\n", ctx->state[0],
	ctx->state[1],
	ctx->state[2],
	ctx->state[3],
	ctx->state[4],
	ctx->state[5],
	ctx->state[6],
	ctx->state[7]);
}

static t_uint32    ror64(t_uint64 v, t_uint16 n)
{
    return ((v >> n) | (v << (64-n)));
}

t_uint64    ch(t_uint64 x, t_uint64 y, t_uint64 z)
{
    return ((x & y) | (~x & z));
}

t_uint64    maj(t_uint64 x, t_uint64 y, t_uint64 z)
{
    return ((x & y) | (x & z) | (y & z)); 
}

t_uint64    up_sig0(t_uint64 x)
{
    return (ror64(x, 28) ^ ror64(x, 34) ^ ror64(x, 39));
}

t_uint64    up_sig1(t_uint64 x)
{
    return (ror64(x, 14) ^ ror64(x, 18) ^ ror64(x, 41));
}

t_uint64    low_sig0(t_uint64 x)
{
    return (ror64(x, 1) ^ ror64(x, 8) ^ (x >> 7));
}

t_uint64    low_sig1(t_uint64 x)
{
    return (ror64(x, 19) ^ ror64(x, 61) ^ (x >> 6));
}

void		sha512_init(SHA512_CTX *ctx)
{
	printf("\tEntering sha512_init\n");
	ctx->datalen = 0;
	ctx->bitlen = 0;
	ctx->state[0] = 0x6a09e667f3bcc908;
	ctx->state[1] = 0xbb67ae8584caa73b;
	ctx->state[2] = 0x3c6ef372fe94f82b;
	ctx->state[3] = 0xa54ff53a5f1d36f1;
	ctx->state[4] = 0x510e527fade682d1;
	ctx->state[5] = 0x9b05688c2b3e6c1f;
	ctx->state[6] = 0x1f83d9abfb41bd6b;
	ctx->state[7] = 0x5be0cd19137e2179;
	print_states(ctx, 1);
	printf("\tExitting sha512_init\n\n");
}

void sha512_transform(SHA512_CTX *ctx, const BYTE data[])
{
	t_uint64	a, b, c, d, e, f, g, h, i, t1, t2;
	t_uint64	*m = ctx->word;

	printf("\t\tEntering sha512_transform\n");

	for (i = 0; i < 16; i++)
		m[i] = SWAP64(m[i]);
	printf("test:\n");
	for (int x = 0; x < 16; x++)
		printf(" - %lx\n", m[x]);

	a = ctx->state[0];
	b = ctx->state[1];
	c = ctx->state[2];
	d = ctx->state[3];
	e = ctx->state[4];
	f = ctx->state[5];
	g = ctx->state[6];
	h = ctx->state[7];

	for (i = 0; i < 80; i++)
	{
		if (i >= 16)
			M(i) += low_sig1(M(i + 14)) + M(i + 9) + low_sig0(M(i +1));
		t1 = h + up_sig1(e) + ch(e,f,g) + k[i] + M(i);
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
	printf("\t\tExitting sha512_transform\n");
}

void sha512_update(SHA512_CTX *ctx, const BYTE data[], size_t len)
{
	DWORD i;

	printf("\tEntering sha512_update\n");
	for (i = 0; i < len; i++) {
		ctx->data[ctx->datalen] = data[i];
		ctx->datalen++;
		if (ctx->datalen == 128) {
			sha512_transform(ctx, ctx->data);
			ctx->bitlen += 1024;
			ctx->datalen = 0;
		}
	}
	print_states(ctx, 1);
	printf("\tExitting sha512_update\n\n");
}

void sha512_final(SHA512_CTX *ctx, BYTE hash[])
{
	DWORD i;

	printf("\tEntering sha512_final\n");
	i = ctx->datalen;

	if (ctx->datalen < 112) {
		ctx->data[i++] = 0x80;
		while (i < 112)
			ctx->data[i++] = 0x00;
	}
	else {
		ctx->data[i++] = 0x80;
		while (i < 128)
			ctx->data[i++] = 0x00;
		sha512_transform(ctx, ctx->data);
		memset(ctx->data, 0, 112);
	}

	ctx->bitlen += ctx->datalen * 8;
	ctx->word[14] = 0;
	ctx->word[15] = SWAP64(ctx->bitlen);
	printf("test: 0x");
	for (int x = 0; x < 128; x++)
		printf("%x", ctx->data[x]);
	printf("\n");

	sha512_transform(ctx, ctx->data);

	for (i = 0; i < 8; i++)
		ctx->state[i] = SWAP64(ctx->state[i]);
	memcpy(hash, ctx->digest, 64);

	print_states(ctx, 1);
	printf("\tExitting sha512_final\n");
}

void    block_to_str(char *str, u_sha512 block)
{
	BYTE	    i;
	char        j;
	char        n;

	i = 0;
	while (i < 8)
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
	str[16] = '\0';
}

char	*sha_test(char *msg, unsigned len)
{
	SHA512_CTX	*context;
	BYTE		digest[64];
	char		*hash;
	char		s[17];

	if (!(hash = malloc(129)))
		return (NULL);
	bzero(hash, 129);

	if (!(context = malloc(sizeof(SHA512_CTX))))
	{
		free(hash);
		return (NULL);
	}
	printf("Allocations OK\n");
	sha512_init(context);
	sha512_update(context, msg, len);
	sha512_final(context, (BYTE *)digest);

	free(context);
	printf("Context Free'd\n");
	int			i = 0;
	u_sha512	block;
	while (i < 8)
	{
		block.word = ((DWORD *)digest)[i];
		bzero(s, 17);
		block_to_str((char *)s, block);
		strcat(hash, s);
		i++;
	}
	return (hash);
}

int		main(int argc, char **argv)
{
	int				fd;
	struct stat		file_stats;
	char			*file_content;
	char			*final_hash;

	fd = open(argv[1], O_RDONLY);
	fstat(fd, &file_stats);
	printf("File name: %s\nFile size: %u\n\n", argv[1], file_stats.st_size);
	file_content = mmap(NULL, file_stats.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	final_hash = sha_test(file_content, file_stats.st_size);
	printf("\nFinal hash:\n%s\n", final_hash);
	(void)argc;
	return (0);
}
