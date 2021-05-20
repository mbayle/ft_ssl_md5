#include "ft_ssl.h"

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

#include <stdio.h>
static t_opt	get_options(char **args, int count)
{
	t_uint32	i;
	t_opt		options;

	i = 0;
	ft_bzero(&options, sizeof(t_opt));
	while (count--)
	{
		if (!(args[i][0] == '-'))
			break ;
		if (ft_strchr(OPT_CHARSET, args[i][1]) && !args[i][2])
			set_option(&options, args[i][1]);
		else
		{
			options.err = TRUE;
			break ;
		}
		if (args[i][1] == 's')
			break ;
		i++;
	}
	return (options);
}

static void			cipher_error(char *command)
{
	write(STDERR, "ft_ssl: Error: \'", 16);
	write(STDERR, command, ft_strlen(command));
	write(STDERR, "\' is an invlaid command.\n", 25);
	write(STDERR, "\nMessage Digest commands:\nmd5\t\tsha256\nsha512\t\twhirlpool\n", 56);
}

static t_cipher		get_cipher(char	*cipher)
{
	if (!ft_strcmp(cipher, "md5") || !ft_strcmp(cipher, "MD5"))
		return (MD5);
	if (!ft_strcmp(cipher, "sha256") || !ft_strcmp(cipher, "SHA256"))
		return (SHA256);
	if (!ft_strcmp(cipher, "sha512") || !ft_strcmp(cipher, "SHA512"))
		return (SHA512);
	if (!ft_strcmp(cipher, "whirlpool") || !ft_strcmp(cipher, "WHIRLPOOL"))
		return (WHIRLPOOL);
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
        if (args[i][1] == 'o' || args[i][1] == 's')
			return (i + 1);
        i++;
    }
    return (i);
}

int		main(int argc, char **argv)
{
    t_cipher		cipher;
	t_opt	    	options;
    int             args_start;

	if (argc == 1)
	{
		print_usage();
		return (ERR_NO_ARGS);
	}
	cipher = get_cipher(argv[1]);
	if (cipher == ERROR)
	{
		cipher_error(argv[1]);
		exit (ERR_BAD_CIPHER);
	}
	options = get_options(&argv[2], argc - 2);
	if (options.err == TRUE)
		return (ERR_BAD_OPTION);
    args_start = get_last_option(argv, argc);
    hash_message(cipher, options, &argv[args_start], argc - args_start);
	return (SUCCESS);
}
