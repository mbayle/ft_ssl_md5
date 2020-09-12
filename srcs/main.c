#include "ft_ssl.h"
#include <stdio.h>

static void		set_option(t_opt *options, char flag)
{
	if (flag == 'p')
		options->p = TRUE;
	if (flag == 'q')
		options->q = TRUE;
	if (flag == 'r')
		options->r = TRUE;
	if (flag == 's')
		options->s = TRUE;
	if (flag == 'o')
		options->o = TRUE;
}

static t_opt	*get_options(char **args, int count)
{
	t_uint32	i;
	t_opt		*options;

	i = 0;
	if (!(options = malloc(sizeof(t_opt))))
		exit (ERR_NO_MEM);
	ft_bzero(options, sizeof(t_opt));
	while (count--)
	{
		if (!(args[i][0] == '-'))
			break ;
		if (ft_strchr(OPT_CHARSET, args[i][1]) && !args[i][2])
			set_option(options, args[i][1]);
		else
		{
			free(options);
			return (NULL);
		}
		if (args[i][1] == 's')
			break ;
		i++;
	}
	return (options);
}

static char		get_cipher(char	*cipher)
{
	if (!ft_strcmp(cipher, "md5") || !ft_strcmp(cipher, "MD5"))
		return (MD5);
	if (!ft_strcmp(cipher, "sha256") || !ft_strcmp(cipher, "SHA256"))
		return (SHA256);
	return (-1);
}

int		main(int argc, char **argv)
{
	char		cipher;
	t_opt		*options;

	if (argc == 1)
	{
		print_usage();
		return (ERR_NO_ARGS);
	}
	cipher = get_cipher(argv[1]);
	if (cipher < 0)
		exit (ERR_BAD_CIPHER);
	options = get_options(&argv[2], argc - 2);
	if (options == NULL)
		return (ERR_BAD_OPTION);
	return (SUCCESS);
}
