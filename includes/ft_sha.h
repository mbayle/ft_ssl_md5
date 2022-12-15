#ifndef FT_SHA256_H
# define FT_SHA256_H

/* Context state constants */
# define SHA256_STATE1	0x6A09E667
# define SHA256_STATE2	0xBB67AE85
# define SHA256_STATE3	0x3C6EF372
# define SHA256_STATE4	0xA54FF53A
# define SHA256_STATE5	0x510E527F
# define SHA256_STATE6	0x9B05688C
# define SHA256_STATE7	0x1F83D9AB
# define SHA256_STATE8	0x5BE0CD19

#define SHA512_HASH_SIZE		64
#define SHA512_BLOCK_SIZE		128

typedef unsigned char	t_uint8;
typedef unsigned short	t_uint16;
typedef unsigned int	t_uint32;
typedef unsigned long	t_uint64;

/* sha256 context */
typedef struct {
	t_uint32		state[8];
	t_uint8			buffer[64];
	t_uint32		datalen;
	t_uint64		bitlen;
} t_sha256_context;

typedef union	shaunion_256
{
	t_uint32		word;
	t_uint8			byte[4];
}				u_sha256;

/* sha512 context */
typedef struct sha512_ctx
{
	t_uint64	message[16];
	t_uint64	length;
	t_uint64	hash[8];
	unsigned	digest_length;
} sha512_ctx;

typedef union	shaunion_512
{
	t_uint64	word;
	t_uint8		byte[8];
}				u_sha512;

/* Macro definitions (should be temporary) */
#define I64(x)				x##ULL
#define IS_ALIGNED_64(p)	(0 == (7 & ((const char*)(p) - (const char*)0)))

#define ROTR64(qword, n) ((qword) >> (n) ^ ((qword) << (64 - (n))))

/* Optimized version of Ch(x,y,z)=((x & y) | (~x & z)) */
#define Ch(x,y,z)  ((z) ^ ((x) & ((y) ^ (z))))
/* Optimized version of Maj(x,y,z)=((x & y) ^ (x & z) ^ (y & z)) */
#define Maj(x,y,z) (((x) & (y)) ^ ((z) & ((x) ^ (y))))

#define Sigma0(x) (ROTR64((x), 28) ^ ROTR64((x), 34) ^ ROTR64((x), 39))
#define Sigma1(x) (ROTR64((x), 14) ^ ROTR64((x), 18) ^ ROTR64((x), 41))
#define sigma0(x) (ROTR64((x),  1) ^ ROTR64((x),  8) ^ ((x) >> 7))
#define sigma1(x) (ROTR64((x), 19) ^ ROTR64((x), 61) ^ ((x) >> 6))

#define RECALCULATE_W(W,n) (W[n] += \
			(sigma1(W[(n - 2) & 15]) + W[(n - 7) & 15] + sigma0(W[(n - 15) & 15])))

#define ROUND(a,b,c,d,e,f,g,h,k,data) { \
		t_uint64 T1 = h + Sigma1(e) + Ch(e,f,g) + k + (data); \
		d += T1, h = T1 + Sigma0(a) + Maj(a,b,c); }
#define ROUND_1_16(a,b,c,d,e,f,g,h,n) \
		ROUND(a,b,c,d,e,f,g,h, ck[n], W[n] = be2me_64(block[n]))
#define ROUND_17_80(a,b,c,d,e,f,g,h,n) \
		ROUND(a,b,c,d,e,f,g,h, k[n], RECALCULATE_W(W, n))

/* operation.c */
t_uint32    ch(t_uint32 x, t_uint32 y, t_uint32 z);
t_uint32    maj(t_uint32 x, t_uint32 y, t_uint32 z);
t_uint32    up_sig0(t_uint32 x);
t_uint32    up_sig1(t_uint32 x);
t_uint32    low_sig0(t_uint32 x);
t_uint32    low_sig1(t_uint32 x);

/* sha256.c */
char    *sha256(const char *msg, t_uint32 len);

/* sha512.c */
char    *sha512(const char *msg, t_uint32 len);

#endif
