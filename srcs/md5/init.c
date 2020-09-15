#include "ft_ssl.h"
#include "ft_md5.h"

t_uint32	*calctable(unsigned *k)
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
