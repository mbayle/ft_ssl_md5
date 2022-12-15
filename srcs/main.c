#include "ft_ssl.h"
#include "ft_md5.h"

/*! \fn static void		set_option(t_opt *opt, char flag)
 *
 *  @param[in] [opt] Struct t_opt
 *  @param[in] [flag] Flag to find
 */
static void		set_option(t_opt *opt, char flag)
{
	if (flag == 'p')
		opt->p = TRUE;
	if (flag == 'q')
		opt->q = TRUE;
	if (flag == 'r')
		opt->r = TRUE;
	if (flag == 's')
		opt->s = TRUE;
}

/*! \fn static t_opt	get_opt(char **args, int count)
 *  \brief Lists and retrieves flags.
 *          Check validity and display error if flag does not exist
 * 
 *  @param[in] [args] Arguments of function
 *  @param[in] [count] Number of argument to test
 */
static t_opt	get_opt(char **args, int count)
{
	t_uint16	i;
	t_uint16	c;
	t_opt		opt;

	i = 0;
	ft_bzero(&opt, sizeof(t_opt));
	while (count--)
	{
		c = 1;
		if (!(args[i][0] == '-'))
			break ;
		while (args[i][c])
		{
			if (ft_strchr(OPT_CHARSET, args[i][c]))
				set_option(&opt, args[i][c]);
			else
			{
                fprintf(stderr, "\e[0;31m" "Error: "
                        "\e[0m"  "option %s is invalid\n\n"
                        "\033[0;33m" "Available flag: "
                        "\e[0m" "[-pqrs]\n", args[i]);
				opt.err = TRUE;
				break ;
			}
			c++;
		}
		if (args[i][1] == 's')
			break ;
		i++;
	}
	return (opt);
}

/*! \fn static int     get_last_option(char **args, int n)
 *
 *  @param[in] [args] Arguments of function
 *  @param[in] [n] Position
 */
static int     get_last_option(char **args, int n)
{
    int        i;

    i = 2;
    while (i < n)
    {
        if (args[i][0] != '-')
            break ;
        if (args[i][1] == 's')
			return (i + 1);
        i++;
    }
    return (i);
}

/*! \fn static t_cipher		get_cipher(char	*cipher)
 *  \brief Search for a match between input and cipher available
 *
 *  @param[in] [cipher] Cipher find in command
 */
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

/*! \fn int main(int argc, char** argv)
 */
int main(int argc, char** argv)
{
    t_cipher    cipher;
    t_opt       opt;
    int         arg_start;

    if (argc == 1)
    {
        printf("%s", "usage: ft_ssl [cipher] [-pqro] [-s string] [files ...]\n");
        return ERR_NO_ARGS; 
    }
    cipher = get_cipher(argv[1]);
    if (cipher == ERROR)
    {
        fprintf(stderr, "\e[0;31m" "Error: "
            "\e[0m"  "%s is an invalid command.\n\n"
            "\033[0;33m" "Available command:\n"
            "\e[0m" "md5\n"
			"\e[0m" "sha256\n"
			"\e[0m" "sha512\n"
			"\e[0m" "whirlpool\n\n"
			"\033[0;33m" "Flags\n"
			"\e[0m" "-p -q -r -s\n", argv[1]);
        exit (ERR_BAD_CIPHER);
    }
    opt = get_opt(&argv[2], argc - 2);
	if (opt.err == TRUE)
		return (ERR_BAD_OPTION);
    arg_start = get_last_option(argv, argc);
    hash_message(cipher, opt, &argv[arg_start], argc - arg_start);
	return (SUCCESS);
}