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

static char         *read_iterator(hash_fn hash, size_t read_size, int fd)
{
    static t_uint32	last_len = 0;
    t_uint32    	len;
    char        	*buf;
    char        	*result;
    
    result = NULL;
    if (!(buf = malloc(read_size + 1)))
        return (NULL);
    ft_bzero(buf, read_size + 1);
    while((len = read(fd, buf, read_size)) > 0)
    {
        result = hash(buf, len);
		ft_bzero(buf, read_size + 1);
        last_len = len;
    }
    if (last_len == read_size || last_len == 0)
        result = hash(NULL, 0);
    free(buf);
    return (result);
}

char                hash_message(const t_cipher cipher, const t_opt options, char **args, int count)
{
    static hash_fn      *func_tab = NULL;
    static size_t       *sizes_tab = NULL;
    int                 fd;
    int                 i;
    char                *result;

    fd = 0;
    i = 0;
    if (func_tab == NULL)
        if (!(func_tab = init_func_tab()))
            return (ERR_NO_MEM);
    if (sizes_tab == NULL)
        if (!(sizes_tab = init_sizes_tab()))
            return (ERR_NO_MEM);
    if (count == 0)
        result = read_iterator(func_tab[cipher], sizes_tab[cipher], 1);
    while (i < count)
    {
        if ((fd = open(args[i], O_RDONLY)) == -1)
        {
            free(sizes_tab);
            free(func_tab);
            return (ERR_OPEN);
        }
        result = read_iterator(func_tab[cipher], sizes_tab[cipher], fd);
        close(fd);
        i++;
    }
    display_hash(result, options, cipher, args[0]);
	free(result);
    free(sizes_tab);
    free(func_tab);
    return (SUCCESS);
}
