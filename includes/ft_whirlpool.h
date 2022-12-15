/* whirlpool.h */
#ifndef WHIRLPOOL_H
#define WHIRLPOOL_H

#include <stdlib.h>

#define whirlpool_block_size 64
typedef unsigned char	t_uint8;
typedef unsigned short	t_uint16;
typedef unsigned int	t_uint32;
typedef unsigned long	t_uint64;

#define I64(x)	x##ULL

/* algorithm context */
typedef struct whirlpool_ctx
{
	t_uint64 hash[8];    /* 512-bit algorithm internal hashing state */
	unsigned char message[whirlpool_block_size]; /* 512-bit buffer to hash */

	/* Note: original algorith uses 256-bit counter, allowing to hash up to
	   2^256 bits sized message. For optimization we use here 64-bit counter,
	   thus reducing maximal message size to 2^64 bits = 2 Exbibytes = 2^21 TiB) */
	t_uint64 length;     /* number of processed bytes */
} whirlpool_ctx;

typedef union	WHIRLPOOLunion
{
	t_uint64	result;
	t_uint8		byte[8];
}				WHIRLPOOLunion;

/* hash functions */
char *whirlpool(const char *msg, t_uint32 len);
void whirlpool_init(whirlpool_ctx* ctx);
void whirlpool_update(whirlpool_ctx* ctx, const unsigned char* msg, size_t size);
void whirlpool_final(whirlpool_ctx* ctx, unsigned char* result);

#endif /* WHIRLPOOL_H */