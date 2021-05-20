#include "ft_ssl.h"
#include "ft_md5.h"
#include "ft_sha.h"
#include "ft_whirlpool.h"

static hash_fn  *init_func_tab(void)
{
    hash_fn     *func_tab;

    if (!(func_tab = malloc(sizeof(hash_fn) * NB_OF_CIPHERS)))
        return (NULL);
    func_tab[MD5] = &md5;
    func_tab[SHA256] = &sha256;
    func_tab[SHA512] = &sha512;
	func_tab[WHIRLPOOL] = &whirlpool;
    return (func_tab);
}

static size_t     *init_sizes_tab(void)
{
    size_t        *sizes_tab;

    if (!(sizes_tab = malloc(sizeof(t_uint64) * NB_OF_CIPHERS)))
        return (NULL);
    sizes_tab[MD5] = 64;
    sizes_tab[SHA256] = 64;
    sizes_tab[SHA512] = 128;
    sizes_tab[WHIRLPOOL] = 64;
    return (sizes_tab);
}

static char         *read_iterator(hash_fn hash, size_t read_size, int fd, t_uint8 print)
{
    t_uint32		last_len;
    t_uint32    	len;
    char        	*buf;
    char        	*result;
    
    result = NULL;
	last_len = 0;
    if (!(buf = malloc(read_size + 1)))
        return (NULL);
    ft_bzero(buf, read_size + 1);
    while((len = read(fd, buf, read_size)) > 0)
    {
		if (print)
			write(1, buf, len);
        result = hash(buf, len);
		ft_bzero(buf, read_size + 1);
        last_len = len;
    }
    if (last_len == read_size || last_len == 0)
        result = hash(NULL, 0);
    free(buf);
    return (result);
}

static char         *hash_string(hash_fn hash, size_t read_size, char *string)
{
    size_t			last_len;
    size_t	    	len;
    char        	*buf;
    char        	*result;
    
    result = NULL;
	last_len = 0;
    if (!(buf = malloc(read_size + 1)))
        return (NULL);
    ft_bzero(buf, read_size + 1);
    while((len = ft_strlen(string)) > 0)
    {
		ft_memcpy(buf, string, read_size);
        result = hash(buf, len);
		ft_bzero(buf, read_size + 1);
		if (len > read_size)
			len = read_size;
		last_len = len;
		string += len;
    }
    if (last_len == read_size || last_len == 0)
        result = hash(NULL, 0);
    free(buf);
    return (result);
}

static void			print_open_err(char *file)
{
	if (access(file, F_OK) < 0)
	{
		write(STDERR, "ft_ssl: Error: \'", 16);
		write(STDERR, file, ft_strlen(file));
		write(STDERR, "\' does not exist.\n", 18);
	}
	else
	{
		write(STDERR, "ft_ssl: Error: insufficient rights to read \'", 44);
		write(STDERR, file, ft_strlen(file));
		write(STDERR, "\'.\n", 3);
	}
}

char                hash_message(const t_cipher cipher, t_opt options, char **args, int count)
{
    static hash_fn      *func_tab = NULL;
    static size_t       *sizes_tab = NULL;
    int                 fd;
    int                 i;
    char                *result;
	char				return_value;

    fd = 0;
    i = 0;
	return_value = SUCCESS;
    if (func_tab == NULL)
        if (!(func_tab = init_func_tab()))
            return (ERR_NO_MEM);
    if (sizes_tab == NULL)
        if (!(sizes_tab = init_sizes_tab()))
        {
            free(func_tab);    
            return (ERR_NO_MEM);
        }
    if (count == 0 || options.p == TRUE)
	{
        result = read_iterator(func_tab[cipher], sizes_tab[cipher], 0, TRUE);
		display_hash(result, options, cipher, "stdin", FALSE);
		options.p = FALSE;
		free(result);
	}
	if (options.s == TRUE)
	{
		result = hash_string(func_tab[cipher], sizes_tab[cipher], args[i]);
		display_hash(result, options, cipher, args[i], TRUE);
		i++;
	}
    while (i < count)
    {
        if ((fd = open(args[i], O_RDONLY)) == -1)
        {
            return_value = ERR_OPEN;
			print_open_err(args[i]);
			i++;
			continue ;
        }
        result = read_iterator(func_tab[cipher], sizes_tab[cipher], fd, FALSE);
		display_hash(result, options, cipher, args[i], FALSE);
        close(fd);
		free(result);
        i++;
    }
    free(sizes_tab);
    free(func_tab);
    return (return_value);
}
