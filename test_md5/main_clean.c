#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define PRINT_SEPARATOR() printf("~~~~~~~~~~~~~~~~~~~~~\n");

/* M table constant */
#define M0	1
#define M1	5
#define	M2	3
#define M3	7

/* O table constant */
#define O0	0
#define O1	1
#define	O2	5
#define O3	0

/* ROT CONSTANT */
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

typedef unsigned char	t_uint8;
typedef unsigned short	t_uint16;
typedef unsigned int	t_uint32;
typedef unsigned long	t_uint64;

/* md5 context */
typedef struct {
	t_uint32		state[4];                                   /* state (ABCD) */
	t_uint32 		count[2];        /* number of bits, modulo 2^64 (lsb first) */
	unsigned char	buffer[64];                         /* input buffer */
} t_md5_ctx;

typedef union	md5union
{
	t_uint32	word;
	t_uint8		byte[4];
}				u_md5;

typedef union 	blkunion{
	unsigned	word[16];
	char		str[64];
}				u_block;

typedef unsigned (*digest_fn)(unsigned a[]);

unsigned func0( unsigned v[] )
{
	return ( v[1] & v[2]) | (~v[1] & v[3]);
}

unsigned func1( unsigned v[] )
{
	return ( v[3] & v[1]) | (~v[3] & v[2]);
}

unsigned func2( unsigned v[] )
{
	return  v[1] ^ v[2] ^ v[3];
}

unsigned func3( unsigned v[] )
{
	return v[2] ^ (v[1] |~ v[3]);
}

static t_uint32		rol32(t_uint32 v, t_uint16 n)
{
	t_uint32	mask;

	mask = (1 << n) - 1;
	return ((v >> (32 - n)) & mask) | ((v << n) & ~mask);
}

t_uint32	 *calctable(unsigned *k)
{
	double	s;
	double	pwr;
	int		i;

	i = 0;
	k = malloc(sizeof(t_uint32) * 64);
	pwr = pow(2.0, 32);
	while (i < 64)
	{
		s = fabs(sin(1.0 + i));
		k[i] = (unsigned)(s * pwr);
		i++;
	}
	return k;
}

t_md5_ctx	*context_init(void)
{
	t_md5_ctx	*context;

	context = malloc(sizeof(t_md5_ctx));
	context->count[0] = 0;
	context->count[1] = 0;
	context->state[0] = 0x67452301;
	context->state[1] = 0xEFCDAB89;
	context->state[2] = 0x98BADCFE;
	context->state[3] = 0x10325476;
	return (context);
}

t_uint8		*md5_pad_msg(t_uint8 *msg, t_uint32 len, t_uint32 grps)
{
	int q;

	printf("Setting the 0x80\n\n");
	msg[len] = (unsigned char)0x80;
	q = len + 1;
	while (q < 64 * grps) { msg[q] = 0; q++; }
	{
		u_md5 u;
		u.word = 8 * len;
		q -= 8;
		memcpy(msg + q, &u.word, 4);
	}
	return (msg);
}

t_uint32	*hash_msg_md5(const char *msg, t_uint32 len)
{
	static digest_fn	funcs[] = { &func0, &func1, &func2, &func3 };
	static short		rot0[] = { S11, S12, S13, S14 };
	static short		rot1[] = { S21, S22, S23, S24 };
	static short		rot2[] = { S31, S32, S33, S34 };
	static short		rot3[] = { S41, S42, S43, S44 };
	static short		*rots[] = { rot0, rot1, rot2, rot3 };
	static t_uint32		*k = NULL;
	static t_md5_ctx	*context = NULL;
	u_block				block;

	int grp, grps, q, p; // miscellaneous counters
	unsigned char *msg2;

	/* Don't know what the following are yet */
	static short M[] = { M0, M1, M2, M3 };
	static short O[] = { O0, O1, O2, O3 };
	t_uint32 f;
	t_uint32 abcd[4];
	short m, o, g;

	if (context == NULL)
		context = context_init();	// initializing states

	if (k == NULL)
		k = calctable(k);				// initializing the static k table

	grps = 1 + (len + 8) / 64;			// determining the numbers of groups from the total msg len
	printf("Number of groups: %u (msglen: %u)\n\n", grps, len);
	msg2 = (unsigned char*)malloc(64 * grps); // will be replaced by the read loop
	memcpy(msg2, msg, len);
	msg2 = md5_pad_msg(msg2, len, grps);

	for (grp = 0; grp<grps; grp++)
	{
		printf("handling \"%s\"\n", msg2);
		printf("current context: %#lx, %#lx, %#lx, %#lx\n\n", context->state[0], context->state[1], context->state[2], context->state[3]);
		memcpy(block.str, msg2, 64);
		for (q = 0; q<4; q++) abcd[q] = context->state[q]; //abcd = h

		for (p = 0; p<4; p++) {
			m = M[p];
			o = O[p];
			for (q = 0; q<16; q++) {
				g = (m*q + o) % 16;
				f = abcd[1] + rol32(abcd[0] + funcs[p](abcd) + k[q + 16 * p] + block.word[g], rots[p][q % 4]);

				abcd[0] = abcd[3];
				abcd[3] = abcd[2];
				abcd[2] = abcd[1];
				abcd[1] = f;
			}
		}
		for (p = 0; p<4; p++)
		{
			context->state[p] += abcd[p];
		}
		msg2 += 64;
	}
	return context->state;
}

const char	*get_md5(const char *msg)
{
	u_md5		block;
	t_uint32	i;
	t_uint32	*digest;
	char		*hash;
	char		s[8];

	hash = malloc(33);
	bzero(hash, 33);
	i = 0;
	digest = hash_msg_md5(msg, strlen(msg));
	while (i < 4)
	{
		block.word = digest[i];
		sprintf(s, "%02x%02x%02x%02x", block.byte[0], block.byte[1], block.byte[2], block.byte[3]);
		strcat(hash, s);
		i++;
	}
	return (hash);
}

int		main(int argc __attribute__((unused)), char **argv)
{
	const char	*hash;

	printf("input: %s\n", argv[1]);
	PRINT_SEPARATOR();
	hash = get_md5(argv[1]);
	PRINT_SEPARATOR();
	printf("output: %s\n", hash);
}
