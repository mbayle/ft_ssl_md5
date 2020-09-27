#include "ft_ssl.h"
#include "ft_md5.h"

#include <stdio.h>
t_uint8		*md5_pad_msg(t_uint8 *msg, t_uint32 len)
{
    int q;

    printf("Setting the 0x80\n\n");
    msg[len] = (unsigned char)0x80;
    q = len + 1;
    while (q < 64) 
        msg[q++] = 0;
    u_md5 u;
    u.word = 8 * len;
    q -= 8;
    ft_memcpy(msg + q, &u.word, 4);
    return (msg);
}

t_uint32	*hash_msg_md5(const char *msg, t_uint32 len)
{
	static t_uint32     total_len = 0;
    t_uint8             *msg2;
    
    static digest_fn	funcs[] = { &func0, &func1, &func2, &func3 };
	static short		rot0[] = { S11, S12, S13, S14 };
	static short		rot1[] = { S21, S22, S23, S24 };
	static short		rot2[] = { S31, S32, S33, S34 };
	static short		rot3[] = { S41, S42, S43, S44 };
	static short		*rots[] = { rot0, rot1, rot2, rot3 };
	static t_uint32		*k = NULL;
	static t_md5_ctx	*context = NULL;
	u_block				block;

	int                 q;
    int                 p; // miscellaneddous counters

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

    if (!(msg2 = malloc(65)))
        return (NULL);
    ft_bzero(msg2, 65);
    ft_memcpy(msg2, msg, len);

    total_len += len;

    if (len < 64)
        msg2 = md5_pad_msg(msg2, total_len);

    printf("handling \"%s\"\n", msg2);
    printf("current context: %#x, %#x, %#x, %#x\n\n", context->state[0], context->state[1], context->state[2], context->state[3]);
    ft_memcpy(block.str, msg2, 64);
    for (q = 0; q<4; q++)
        abcd[q] = context->state[q]; //abcd = h

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

	return context->state;
}

#include <string.h>
char	*md5(const char *msg, t_uint32 len)
{
	u_md5		block;
	t_uint32	i;
	t_uint32	*digest;
	char		*hash;
	char		s[8];

	if (!(hash = malloc(33)))
        return (NULL);
	ft_bzero(hash, 33);
	i = 0;
	digest = hash_msg_md5(msg, len);
    if (len < 64)
    {
        while (i < 4)
        {
            block.word = digest[i];
            // Replace next function
            sprintf(s, "%02x%02x%02x%02x", block.byte[0], block.byte[1], block.byte[2], block.byte[3]);
            ft_strcat(hash, s);
            i++;
        }
    }
	printf("HASH: %s\n", hash);
	return (hash);
}

