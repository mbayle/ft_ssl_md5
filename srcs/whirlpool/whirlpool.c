#include "ft_ssl.h"
#include "ft_whirlpool.h"
#include "endianness.h"

extern t_uint64	g_whirlpool_sbox[8][256];

static void whirlpool_init(struct whirlpool_ctx* ctx)
{
	ctx->length = 0;
	ft_bzero(ctx->hash, sizeof(ctx->hash));
}

static void whirlpool_transform(t_uint64* hash, t_uint64* p_block)
{
	int			i;
	t_uint64	K[2][8];
	t_uint64	state[2][8];

	unsigned int m = 0;

	const int number_of_rounds = 10;

	static const t_uint64 rc[10] = {
		I64(0x1823c6e887b8014f),
		I64(0x36a6d2f5796f9152),
		I64(0x60bc9b8ea30c7b35),
		I64(0x1de0d7c22e4bfe57),
		I64(0x157737e59ff04ada),
		I64(0x58c9290ab1a06b85),
		I64(0xbd5d10f4cb3e0567),
		I64(0xe427418ba77d95d8),
		I64(0xfbee7c66dd17479e),
		I64(0xca2dbf07ad5a8333)
	};

	for (i = 0; i < 8; i++) {
		K[0][i] = hash[i];
		state[0][i] = be2me_64(p_block[i]) ^ hash[i];
		hash[i] = state[0][i];
	}

	for (i = 0; i < number_of_rounds; i++)
	{
		K[m ^ 1][0] = WHIRLPOOL_OP(K[m], 0) ^ rc[i];
		K[m ^ 1][1] = WHIRLPOOL_OP(K[m], 1);
		K[m ^ 1][2] = WHIRLPOOL_OP(K[m], 2);
		K[m ^ 1][3] = WHIRLPOOL_OP(K[m], 3);
		K[m ^ 1][4] = WHIRLPOOL_OP(K[m], 4);
		K[m ^ 1][5] = WHIRLPOOL_OP(K[m], 5);
		K[m ^ 1][6] = WHIRLPOOL_OP(K[m], 6);
		K[m ^ 1][7] = WHIRLPOOL_OP(K[m], 7);

		state[m ^ 1][0] = WHIRLPOOL_OP(state[m], 0) ^ K[m ^ 1][0];
		state[m ^ 1][1] = WHIRLPOOL_OP(state[m], 1) ^ K[m ^ 1][1];
		state[m ^ 1][2] = WHIRLPOOL_OP(state[m], 2) ^ K[m ^ 1][2];
		state[m ^ 1][3] = WHIRLPOOL_OP(state[m], 3) ^ K[m ^ 1][3];
		state[m ^ 1][4] = WHIRLPOOL_OP(state[m], 4) ^ K[m ^ 1][4];
		state[m ^ 1][5] = WHIRLPOOL_OP(state[m], 5) ^ K[m ^ 1][5];
		state[m ^ 1][6] = WHIRLPOOL_OP(state[m], 6) ^ K[m ^ 1][6];
		state[m ^ 1][7] = WHIRLPOOL_OP(state[m], 7) ^ K[m ^ 1][7];

		m = m ^ 1;
	}

	hash[0] ^= state[0][0];
	hash[1] ^= state[0][1];
	hash[2] ^= state[0][2];
	hash[3] ^= state[0][3];
	hash[4] ^= state[0][4];
	hash[5] ^= state[0][5];
	hash[6] ^= state[0][6];
	hash[7] ^= state[0][7];
}

void whirlpool_update(t_whirlpool_ctx* ctx, const unsigned char* msg, size_t size)
{
	unsigned index = (unsigned)ctx->length & 63;
	unsigned left;
	ctx->length += size;

	if (index) {
		left = BLOCK_SIZE - index;
		ft_memcpy(ctx->message + index, msg, (size < left ? size : left));
		if (size < left)
			return;
		whirlpool_transform(ctx->hash, (t_uint64*)ctx->message);
		msg  += left;
		size -= left;
	}
	while (size >= BLOCK_SIZE) {
		t_uint64* aligned_message_block;
		if (IS_ALIGNED_64(msg)) {
			aligned_message_block = (t_uint64*)msg;
		} else {
			ft_memcpy(ctx->message, msg, BLOCK_SIZE);
			aligned_message_block = (t_uint64*)ctx->message;
		}
		whirlpool_transform(ctx->hash, aligned_message_block);
		msg += BLOCK_SIZE;
		size -= BLOCK_SIZE;
	}
	if (size) {
		ft_memcpy(ctx->message, msg, size);
	}
}

void whirlpool_final(t_whirlpool_ctx* ctx, unsigned char* result)
{
	unsigned index = (unsigned)ctx->length & 63;
	t_uint64* msg64 = (t_uint64*)ctx->message;

	ctx->message[index++] = 0x80;

	if (index > 32) {
		while (index < 64) {
			ctx->message[index++] = 0;
		}
		whirlpool_transform(ctx->hash, msg64);
		index = 0;
	}
	while (index < 56) {
		ctx->message[index++] = 0;
	}
	msg64[7] = be2me_64(ctx->length << 3);
	whirlpool_transform(ctx->hash, msg64);

	be64_copy(result, 0, ctx->hash, 64);
}

void    whirlpoolblock(char *str, u_whirlpool block)
{
	t_uint8	    i;
	char        j;
	char        n;

	i = 0;
	block.word = SWAP64(block.word);
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

static char	*generate_hash(t_whirlpool_ctx *context)
{
	char 		*hash;
	int			i = 0;
	u_whirlpool	block;
	char        s[17];

	if (!(hash = malloc(129)))
		return (NULL);
	ft_bzero(hash, 129);

	while (i < 8)
	{
		block.word = context->hash[i];
		ft_bzero(s, 17);
		whirlpoolblock((char *)s, block);
		ft_strcat(hash, s);
		i++;
	}
	return (hash);
}

char    *whirlpool(const char *msg, t_uint32 len)
{
    static t_whirlpool_ctx	*context = NULL;
	char					*hash;

	hash = NULL;
    if (context == NULL)
    {
        if (!(context = malloc(sizeof(t_whirlpool_ctx))))
            return (NULL);
		whirlpool_init(context);
    }
    whirlpool_update(context, (t_uint8 *)msg , len);
	if (len < BLOCK_SIZE)
	{
		hash = malloc(129);
		whirlpool_final(context, (t_uint8 *)hash);
		free(hash);
		hash = generate_hash(context);
		free(context);
		context = NULL;
	}
	return (hash);
}
