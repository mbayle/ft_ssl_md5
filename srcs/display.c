#include "ft_ssl.h"

static void print_filename(char *file_name, int fd, t_uint8 is_string)
{
	if (is_string)
		write(fd, "(\"", 2);
	else
		write(fd, "(", 1);
	write(fd, file_name, ft_strlen(file_name));
	if (is_string)
		write(fd, "\")= ", 4);
	else
		write(fd, ")= ", 3);
}

static void print_cipher(const t_cipher cipher, int fd)
{
	cipher == MD5 ? write(fd, "MD5", 3) : 0;
	cipher == SHA256 ? write(fd, "SHA256", 6) : 0;
	cipher == SHA512 ? write(fd, "SHA512", 6) : 0;
	cipher == WHIRLPOOL ? write(fd, "whirlpool", 9) : 0;
}

void display_hash(char *hash, const t_opt options, const t_cipher cipher, char *file_name, int fd, t_uint8 is_string)
{
	if (!options.r && !options.q)
	{
		print_cipher(cipher, fd);
		print_filename(file_name, fd, is_string);
		write(fd, hash, ft_strlen(hash));
		write(fd, "\n", 1);
	}
	else if (options.q)
	{
		write(fd, hash, ft_strlen(hash));
		write(fd, "\n", 1);
	}
	else if (options.r)
	{
		write(fd, hash, ft_strlen(hash));
		if (is_string)
			write(fd, " \"", 2);
		else
			write(fd, " ", 1);
		write(fd, file_name, ft_strlen(file_name));
		if (is_string)
			write(fd, "\"", 1);
		write(fd, "\n", 1);
	}
}