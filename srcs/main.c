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
	if (!(options = malloc(sizeof(t_opt)))) // We should not allocate that
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

static t_cipher		get_cipher(char	*cipher)
{
	if (!ft_strcmp(cipher, "md5") || !ft_strcmp(cipher, "MD5"))
		return (MD5);
	if (!ft_strcmp(cipher, "sha256") || !ft_strcmp(cipher, "SHA256"))
		return (SHA256);
	return (ERROR);
}

static int     get_last_option(char **args, int n)
{
    int        i;

    i = 2;
    while (i < n)
    {
        if (args[i][0] != '-')
            break ;
        i++;
    }
    return (i);
}

int		main(int argc, char **argv)
{
    t_cipher		cipher;
	t_opt	    	*options;
    int             args_start;

	if (argc == 1)
	{
		print_usage();
		return (ERR_NO_ARGS);
	}
	cipher = get_cipher(argv[1]);
	if (cipher == ERROR)
		exit (ERR_BAD_CIPHER);
	options = get_options(&argv[2], argc - 2);
	if (options == NULL)
		return (ERR_BAD_OPTION);
    args_start = get_last_option(argv, argc);
    hash_message(cipher, *options, &argv[args_start], argc - args_start);
	return (SUCCESS);
}
