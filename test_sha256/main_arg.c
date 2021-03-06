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
	WORD		word;
	BYTE		byte[4];
}				u_sha256;

typedef struct {
	union {
		BYTE data[64];
		WORD word[16];
	};
	WORD datalen;
	unsigned long long bitlen;
	union {
		BYTE digest[32];
		WORD state[8];
	};
} SHA256_CTX;

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

static void		print_states(SHA256_CTX *ctx, BYTE depth)
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

void sha256_init(SHA256_CTX *ctx)
{
	printf("\tEntering sha256_init\n");
	ctx->datalen = 0;
	ctx->bitlen = 0;
	ctx->state[0] = 0x6a09e667;
	ctx->state[1] = 0xbb67ae85;
	ctx->state[2] = 0x3c6ef372;
	ctx->state[3] = 0xa54ff53a;
	ctx->state[4] = 0x510e527f;
	ctx->state[5] = 0x9b05688c;
	ctx->state[6] = 0x1f83d9ab;
	ctx->state[7] = 0x5be0cd19;
	print_states(ctx, 1);
	printf("\tExitting sha256_init\n\n");
}

void sha256_transform(SHA256_CTX *ctx, const BYTE data[])
{
	t_uint32	a, b, c, d, e, f, g, h, i, t1, t2;
	t_uint32	*m = ctx->word;

	printf("\t\tEntering sha256_transform\n");

	for (i = 0; i < 16; i++)
		m[i] = SWAP32(m[i]);
	printf("test:\n");
	for (int x = 0; x < 16; x++)
		printf(" - %x\n", m[x]);

	a = ctx->state[0];
	b = ctx->state[1];
	c = ctx->state[2];
	d = ctx->state[3];
	e = ctx->state[4];
	f = ctx->state[5];
	g = ctx->state[6];
	h = ctx->state[7];

	for (i = 0; i < 64; i++)
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
	printf("\t\tExitting sha256_transform\n");
}

void sha256_update(SHA256_CTX *ctx, const BYTE data[], size_t len)
{
	WORD i;

	printf("\tEntering sha256_update\n");
	for (i = 0; i < len; i++) {
		ctx->data[ctx->datalen] = data[i];
		ctx->datalen++;
		if (ctx->datalen == 64) {
			sha256_transform(ctx, ctx->data);
			ctx->bitlen += 512;
			ctx->datalen = 0;
		}
	}
	print_states(ctx, 1);
	printf("\tExitting sha256_update\n\n");
}

void sha256_final(SHA256_CTX *ctx, BYTE hash[])
{
	WORD i;

	printf("\tEntering sha256_final\n");
	i = ctx->datalen;

	if (ctx->datalen < 56) {
		ctx->data[i++] = 0x80;
		while (i < 56)
			ctx->data[i++] = 0x00;
	}
	else {
		ctx->data[i++] = 0x80;
		while (i < 64)
			ctx->data[i++] = 0x00;
		sha256_transform(ctx, ctx->data);
		memset(ctx->data, 0, 56);
	}

	ctx->bitlen += ctx->datalen * 8;
	ctx->word[14] = 0;
	ctx->word[15] = SWAP32(ctx->bitlen);
	printf("test: 0x");
	for (int x = 0; x < 64; x++)
		printf("%x", ctx->data[x]);
	printf("\n");

	sha256_transform(ctx, ctx->data);

	for (i = 0; i < 8; i++)
		ctx->state[i] = SWAP32(ctx->state[i]);
	memcpy(hash, ctx->digest, 32);

	print_states(ctx, 1);
	printf("\tExitting sha256_final\n");
}

void    block_to_str(char *str, u_sha256 block)
{
	BYTE	    i;
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

char	*sha_test(char *msg, unsigned len)
{
	SHA256_CTX	*context;
	BYTE		digest[32];
	char		*hash;
	char		s[9];

	if (!(hash = malloc(65)))
		return (NULL);
	bzero(hash, 65);

	if (!(context = malloc(sizeof(SHA256_CTX))))
	{
		free(hash);
		return (NULL);
	}
	printf("Allocations OK\n");
	sha256_init(context);
	sha256_update(context, msg, len);
	sha256_final(context, (BYTE *)digest);

	free(context);
	printf("Context Free'd\n");
	int			i = 0;
	u_sha256	block;
	while (i < 8)
	{
		block.word = ((WORD *)digest)[i];
		bzero(s, 8);
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
