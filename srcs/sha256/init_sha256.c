#include "ft_ssl.h"
#include "ft_sha.h"

#include <stdio.h>
void sha256_init(t_sha256_ctx *ctx)
{
	//printf("\tEntering sha256_init\n");
	ctx->datalen = 0;
	ctx->bitlen = 0;
	ctx->state[0] = SHA256_STATE1;
	ctx->state[1] = SHA256_STATE2;
	ctx->state[2] = SHA256_STATE3;
	ctx->state[3] = SHA256_STATE4;
	ctx->state[4] = SHA256_STATE5;
	ctx->state[5] = SHA256_STATE6;
	ctx->state[6] = SHA256_STATE7;
	ctx->state[7] = SHA256_STATE8;
	//print_states(ctx, 1);
	//printf("\tExitting sha256_init\n\n");
}
