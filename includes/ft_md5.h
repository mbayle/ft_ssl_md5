#ifndef FT_MD5_H
# define FT_MD5_H

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

typedef t_uint32 (*digest_fn)(t_uint32 a[]);

/*
** Function prototypes
*/

/* Initialization */
t_uint32	*calctable(unsigned *k);
t_md5_ctx	*context_init(void);

/* Operations */
t_uint32	func0(t_uint32 v[]);
t_uint32	func1(t_uint32 v[]);
t_uint32	func2(t_uint32 v[]);
t_uint32	func3(t_uint32 v[]);
t_uint32	rol32(t_uint32 v, t_uint16 n);

#endif
