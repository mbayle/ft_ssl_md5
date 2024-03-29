#include "ft_ssl.h"
#include "ft_md5.h"

/*! \fn static void	md5_pad_msg(t_uint8 *msg, t_uint32 len, t_uint32 total_len)
 *  \brief Padding gestion
 *
 *  @param[in] [msg] result
 *  @param[in] [len] size
 *  @param[in] [total_len] size of result
 */
static void	md5_pad_msg(t_uint8 *msg, t_uint32 len, t_uint32 total_len)
{
	int		q;
	u_md5	u;

	msg[len] = (unsigned char)0x80;
	q = len + 1;
	while (q < 64) 
		msg[q++] = 0;
	u.word = 8 * total_len;
	q -= 8;
	if (len <= 55)
		ft_memcpy(msg + q, &u.word, 4);
}

/*! \fn t_uint32	*hash_msg_md5(const char *msg, t_uint32 len)
 *  \brief Implementation of md5 algorithm
 *
 *  @param[in] [msg] Message to hash
 *  @param[in] [len] Size of block
 */
t_uint32	*hash_msg_md5(const char *msg, t_uint32 len)
{
	static t_uint32     total_len = 0;
	t_uint8             msg2[65];

	static digest_fn	funcs[] = { &func0, &func1, &func2, &func3 };
	static short		rot0[] = { S11, S12, S13, S14 };
	static short		rot1[] = { S21, S22, S23, S24 };
	static short		rot2[] = { S31, S32, S33, S34 };
	static short		rot3[] = { S41, S42, S43, S44 };
	static short		*rots[] = { rot0, rot1, rot2, rot3 };
	static t_uint32		*k = NULL;
	static t_uint32		*context_states = NULL;
	u_block				block;

	int                 q;
	int                 p;

	/* Don't know what the following are yet */
	static short M[] = { M0, M1, M2, M3 };
	static short O[] = { O0, O1, O2, O3 };
	t_uint32 f;
	t_uint32 abcd[4];
	short m, o, g;

	if (total_len == 0)
	{
		context_states = context_init();
		k = calctable_init();
	}

	ft_bzero(msg2, 65);
	ft_memcpy(msg2, msg, len);

	total_len += len;

	if (len < 64)
		md5_pad_msg((t_uint8 *)msg2, len, total_len);

	ft_memcpy(block.str, msg2, 64);
	q = 0;
	while (q < 4)
	{
		abcd[q] = context_states[q];
		q++;
	}
	p = 0;
	while (p < 4)
	{
		m = M[p];
		o = O[p];
		q = 0;
		while (q < 16)
		{
			g = (m*q + o) % 16;
			f = abcd[1] + rol32(abcd[0] + funcs[p](abcd) + k[q + 16 * p] + block.word[g], rots[p][q % 4]);
			abcd[0] = abcd[3];
			abcd[3] = abcd[2];
			abcd[2] = abcd[1];
			abcd[1] = f;
			q++;
		}
		p++;
	}
	p = 0;
	while (p < 4) 
	{
		context_states[p] += abcd[p];
		p++;
	}
	if (len <= 54)
	{
		total_len = 0;
		free(k);
		k = NULL;
	}
	return context_states;
}

/*! \fn void    block_to_str(char *str, u_md5 block)
 *  \brief Transform result block (hexadecimal) to string
 *
 *  @param[in] [str] Message to hash
 *  @param[in] [block] Size of block
 */
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

/*! \fn char    *md5(const char *msg, t_uint32 len)
 *  \brief MD5 Core (hash msg and transform result into string)
 *
 *  @param[in] [msg] Message to hash
 *  @param[in] [len] Size of block
 */
char	*md5(const char *msg, t_uint32 len)
{
	u_md5		block;
	t_uint32	i;
	t_uint32	*digest;
	char		*hash;
	char		s[9];

	hash = NULL;
	i = 0;
	digest = hash_msg_md5(msg, len);
	if (len < 64)
	{
		if (!(hash = malloc(33)))
			return (NULL);
		ft_bzero(hash, 33);
		if (len > 55)
			digest = hash_msg_md5(NULL, 0);
		while (i < 4)
		{
			block.word = digest[i];
			ft_bzero(s, 8);
			block_to_str((char *)s, block);
			ft_strcat(hash, s);
			i++;
		}
		free(digest);
	}
	return (hash);
}