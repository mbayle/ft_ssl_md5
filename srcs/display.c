#include "ft_ssl.h"

#include <string.h>
static void print_filename(char *file_name, int fd)
{
    write(fd, "(", 1);
    write(fd, file_name, strlen(file_name)); // REPLACE THE STRLEN !!!
    write(fd, ")= ", 3);
}

static void print_cipher(const t_cipher cipher, int fd)
{
    if (cipher == MD5)
        write(fd, "MD5", 3);
    if (cipher == SHA256)
        write(fd, "SHA256", 6);
    if (cipher == SHA512)
        write(fd, "SHA512", 6);
    if (cipher == WHIRLPOOL)
		write(fd, "WHIRLPOOL", 9);
}

void        display_hash(char *hash, const t_opt options, const t_cipher cipher, char *file_name)
{
    int     fd;

    fd = 1;
    if (!options.r && !options.q && !options.p)
    {
		print_cipher(cipher, fd); 
		print_filename(file_name, fd);
		write(fd, hash, strlen(hash));
		write(fd, "\n", 1);
    }
	else if (options.q)
    {
		write(fd, hash, strlen(hash));
		write(fd, "\n", 1);
    }
    else if (options.r)
    {
		write(fd, hash, strlen(hash));
		write(fd, " *", 2);
		write(fd, file_name, strlen(file_name));
		write(fd, "\n", 1);
    }
}
