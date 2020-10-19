#include "ft_ssl.h"
#include "ft_md5.h"

#include <stdio.h>
t_uint8		*md5_pad_msg(t_uint8 *msg, t_uint32 len, t_uint32 total_len)
{
    int		q;
    u_md5	u;

    msg[len] = (unsigned char)0x80;
    q = len + 1;
	printf("q == %d\n", q);
    while (q < 64) 
        msg[q++] = 0;
    u.word = 8 * total_len;
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
	printf("total_len == %u\n", total_len);

    if (len < 64)
        msg2 = md5_pad_msg(msg2, len, total_len);
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
void    block_to_str(char *str, u_md5 block)
{
    t_uint8     i;
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

char	*md5(const char *msg, t_uint32 len)
{
	u_md5		block;
	t_uint32	i;
	t_uint32	*digest;
	char		*hash;
	char		s[9];

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
            ft_bzero(s, 8);
            block_to_str((char *)s, block);
            ft_strcat(hash, s);
            i++;
        }
    }
	return (hash);
}

