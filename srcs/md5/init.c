#include "ft_ssl.h"
#include "ft_md5.h"

#include <math.h>
t_uint32	*calctable_init(void)
{
	double	s;
	double	pwr;
	int		i;
	t_uint32	*k;

	i = 0;
	k = malloc(sizeof(t_uint32) * 64);
	pwr = pow(2.0, 32);
	while (i < 64)
	{
		s = fabs(sin(1.0 + i));
		k[i] = (t_uint32)(s * pwr);
		i++;
	}
	return (k);
}

void		context_init(t_uint32 *states)
{
	states[0] = 0x67452301;
	states[1] = 0xEFCDAB89;
	states[2] = 0x98BADCFE;
	states[3] = 0x10325476;
}
