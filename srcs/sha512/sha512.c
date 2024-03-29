#include "ft_ssl.h"
#include "ft_sha.h"
#include "endianness.h"

static const t_uint64 ck[80] = {
	I64(0x428a2f98d728ae22), I64(0x7137449123ef65cd), I64(0xb5c0fbcfec4d3b2f),
	I64(0xe9b5dba58189dbbc), I64(0x3956c25bf348b538), I64(0x59f111f1b605d019),
	I64(0x923f82a4af194f9b), I64(0xab1c5ed5da6d8118), I64(0xd807aa98a3030242),
	I64(0x12835b0145706fbe), I64(0x243185be4ee4b28c), I64(0x550c7dc3d5ffb4e2),
	I64(0x72be5d74f27b896f), I64(0x80deb1fe3b1696b1), I64(0x9bdc06a725c71235),
	I64(0xc19bf174cf692694), I64(0xe49b69c19ef14ad2), I64(0xefbe4786384f25e3),
	I64(0x0fc19dc68b8cd5b5), I64(0x240ca1cc77ac9c65), I64(0x2de92c6f592b0275),
	I64(0x4a7484aa6ea6e483), I64(0x5cb0a9dcbd41fbd4), I64(0x76f988da831153b5),
	I64(0x983e5152ee66dfab), I64(0xa831c66d2db43210), I64(0xb00327c898fb213f),
	I64(0xbf597fc7beef0ee4), I64(0xc6e00bf33da88fc2), I64(0xd5a79147930aa725),
	I64(0x06ca6351e003826f), I64(0x142929670a0e6e70), I64(0x27b70a8546d22ffc),
	I64(0x2e1b21385c26c926), I64(0x4d2c6dfc5ac42aed), I64(0x53380d139d95b3df),
	I64(0x650a73548baf63de), I64(0x766a0abb3c77b2a8), I64(0x81c2c92e47edaee6),
	I64(0x92722c851482353b), I64(0xa2bfe8a14cf10364), I64(0xa81a664bbc423001),
	I64(0xc24b8b70d0f89791), I64(0xc76c51a30654be30), I64(0xd192e819d6ef5218),
	I64(0xd69906245565a910), I64(0xf40e35855771202a), I64(0x106aa07032bbd1b8),
	I64(0x19a4c116b8d2d0c8), I64(0x1e376c085141ab53), I64(0x2748774cdf8eeb99),
	I64(0x34b0bcb5e19b48a8), I64(0x391c0cb3c5c95a63), I64(0x4ed8aa4ae3418acb),
	I64(0x5b9cca4f7763e373), I64(0x682e6ff3d6b2b8a3), I64(0x748f82ee5defb2fc),
	I64(0x78a5636f43172f60), I64(0x84c87814a1f0ab72), I64(0x8cc702081a6439ec),
	I64(0x90befffa23631e28), I64(0xa4506cebde82bde9), I64(0xbef9a3f7b2c67915),
	I64(0xc67178f2e372532b), I64(0xca273eceea26619c), I64(0xd186b8c721c0c207),
	I64(0xeada7dd6cde0eb1e), I64(0xf57d4f7fee6ed178), I64(0x06f067aa72176fba),
	I64(0x0a637dc5a2c898a6), I64(0x113f9804bef90dae), I64(0x1b710b35131c471b),
	I64(0x28db77f523047d84), I64(0x32caab7b40c72493), I64(0x3c9ebe0a15c9bebc),
	I64(0x431d67c49c100d4c), I64(0x4cc5d4becb3e42b6), I64(0x597f299cfc657e2a),
	I64(0x5fcb6fab3ad6faec), I64(0x6c44198c4a475817)
};

void rhash_swap_copy_str_to_u64(void* to, int index, const void* from, size_t length)
{
	/* if all pointers and length are 64-bits aligned */
	if ( 0 == (( (int)((char*)to - (char*)0) | ((char*)from - (char*)0) | index | length ) & 7) ) {
		/* copy aligned memory block as 64-bit integers */
		const t_uint64* src = (const t_uint64*)from;
		const t_uint64* end = (const t_uint64*)((const char*)src + length);
		t_uint64* dst = (t_uint64*)((char*)to + index);
		while (src < end) *(dst++) = bswap_64( *(src++) );
	} else {
		const char* src = (const char*)from;
		for (length += index; (size_t)index < length; index++) ((char*)to)[index ^ 7] = *(src++);
	}
}

static void sha512_init(sha512_ctx* ctx)
{
	static const t_uint64	SHA512_H0[8] = {
		I64(0x6a09e667f3bcc908), I64(0xbb67ae8584caa73b), I64(0x3c6ef372fe94f82b),
		I64(0xa54ff53a5f1d36f1), I64(0x510e527fade682d1), I64(0x9b05688c2b3e6c1f),
		I64(0x1f83d9abfb41bd6b), I64(0x5be0cd19137e2179)
	};

	ctx->length = 0;
	ctx->digest_length = SHA512_HASH_SIZE;

	/* initialize algorithm state */
	ft_memcpy(ctx->hash, SHA512_H0, sizeof(ctx->hash));
}

static void sha512_transform(t_uint64 hash[8], t_uint64 block[16])
{
	t_uint64		A, B, C, D, E, F, G, H;
	t_uint64		W[16];
	const t_uint64	*k;
	int				i;

	A = hash[0], B = hash[1], C = hash[2], D = hash[3];
	E = hash[4], F = hash[5], G = hash[6], H = hash[7];

	/* Compute SHA using alternate Method: FIPS 180-3 6.1.3 */
	ROUND_1_16(A, B, C, D, E, F, G, H, 0);
	ROUND_1_16(H, A, B, C, D, E, F, G, 1);
	ROUND_1_16(G, H, A, B, C, D, E, F, 2);
	ROUND_1_16(F, G, H, A, B, C, D, E, 3);
	ROUND_1_16(E, F, G, H, A, B, C, D, 4);
	ROUND_1_16(D, E, F, G, H, A, B, C, 5);
	ROUND_1_16(C, D, E, F, G, H, A, B, 6);
	ROUND_1_16(B, C, D, E, F, G, H, A, 7);
	ROUND_1_16(A, B, C, D, E, F, G, H, 8);
	ROUND_1_16(H, A, B, C, D, E, F, G, 9);
	ROUND_1_16(G, H, A, B, C, D, E, F, 10);
	ROUND_1_16(F, G, H, A, B, C, D, E, 11);
	ROUND_1_16(E, F, G, H, A, B, C, D, 12);
	ROUND_1_16(D, E, F, G, H, A, B, C, 13);
	ROUND_1_16(C, D, E, F, G, H, A, B, 14);
	ROUND_1_16(B, C, D, E, F, G, H, A, 15);

	for (i = 16, k = &ck[16]; i < 80; i += 16, k += 16) {
		ROUND_17_80(A, B, C, D, E, F, G, H,  0);
		ROUND_17_80(H, A, B, C, D, E, F, G,  1);
		ROUND_17_80(G, H, A, B, C, D, E, F,  2);
		ROUND_17_80(F, G, H, A, B, C, D, E,  3);
		ROUND_17_80(E, F, G, H, A, B, C, D,  4);
		ROUND_17_80(D, E, F, G, H, A, B, C,  5);
		ROUND_17_80(C, D, E, F, G, H, A, B,  6);
		ROUND_17_80(B, C, D, E, F, G, H, A,  7);
		ROUND_17_80(A, B, C, D, E, F, G, H,  8);
		ROUND_17_80(H, A, B, C, D, E, F, G,  9);
		ROUND_17_80(G, H, A, B, C, D, E, F, 10);
		ROUND_17_80(F, G, H, A, B, C, D, E, 11);
		ROUND_17_80(E, F, G, H, A, B, C, D, 12);
		ROUND_17_80(D, E, F, G, H, A, B, C, 13);
		ROUND_17_80(C, D, E, F, G, H, A, B, 14);
		ROUND_17_80(B, C, D, E, F, G, H, A, 15);
	}

	hash[0] += A, hash[1] += B, hash[2] += C, hash[3] += D;
	hash[4] += E, hash[5] += F, hash[6] += G, hash[7] += H;
}

static void sha512_update(sha512_ctx *ctx, const t_uint8 *msg, size_t size)
{
	size_t index = (size_t)ctx->length & 127;
	ctx->length += size;

	if (index)
	{
		size_t left = SHA512_BLOCK_SIZE - index;
		ft_memcpy((char*)ctx->message + index, msg, (size < left ? size : left));
		if (size < left)
			return;
		sha512_transform(ctx->hash, ctx->message);
		msg  += left;
		size -= left;
	}
	while (size >= SHA512_BLOCK_SIZE)
	{
		t_uint64 *aligned_message_block;
		if (IS_ALIGNED_64(msg))
		{
			aligned_message_block = (t_uint64 *)msg;
		}
		else
		{
			ft_memcpy(ctx->message, msg, SHA512_BLOCK_SIZE);
			aligned_message_block = ctx->message;
		}

		sha512_transform(ctx->hash, aligned_message_block);
		msg  += SHA512_BLOCK_SIZE;
		size -= SHA512_BLOCK_SIZE;
	}
	if (size)
	{
		ft_memcpy(ctx->message, msg, size);
	}
}

static void sha512_final(sha512_ctx* ctx, unsigned char* result)
{
	size_t		index = ((unsigned)ctx->length & 127) >> 3;
	unsigned	shift = ((unsigned)ctx->length & 7) * 8;

	ctx->message[index]   &= le2me_64( ~(I64(0xFFFFFFFFFFFFFFFF) << shift) );
	ctx->message[index++] ^= le2me_64( I64(0x80) << shift );
	if (index >= 15) {
		if (index == 15) ctx->message[index] = 0;
		sha512_transform(ctx->hash, ctx->message);
		index = 0;
	}
	while (index < 15) {
		ctx->message[index++] = 0;
	}
	ctx->message[15] = be2me_64(ctx->length << 3);
	sha512_transform(ctx->hash, ctx->message);

	if (result)
		be64_copy(result, 0, ctx->hash, ctx->digest_length);
}

static void    sha512_block_to_str(char *str, u_sha512 block)
{
	t_uint8	    i;
	char        j;
	char        n;

	i = 0;
	block.word = be2me_64(block.word);
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

char	*sha512(const char *content, t_uint32 size)
{
	static sha512_ctx		*context = NULL;
	char			*hash;
	char			s[17];
	u_sha512		block;
	int				i;

	i = 0;
	hash = NULL;
	if (context == NULL)
	{
		context = malloc(sizeof(sha512_ctx));
		sha512_init(context);
	}
	sha512_update(context, (const t_uint8 *)content, size);
	if (size < 128)
	{
		hash = malloc(129);
		sha512_final(context, (t_uint8 *)hash);
		ft_bzero(hash, 129);
		while (i < 8)
		{
			block.word = ((t_uint64 *)context->hash)[i];
			ft_bzero(s, 17);
			sha512_block_to_str((char *)s, block);
			ft_strcat(hash, s);
			i++;
		}
		free(context);
		context = NULL;
	}
	return (hash);
}