/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 15:01:11 by mabayle           #+#    #+#             */
/*   Updated: 2020/04/20 16:03:43 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <stdlib.h>
# include <limits.h>

# define SEPARATOR '\n'
# define FRED "\033[0;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[0;m"
# define BGREEN "\033[0;30;42m"
# define BCYAN "\033[0;30;46m"
# define BYELLOW "\033[0;30;43m"
# define BUFF_SIZE 32

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

/*
********************************************************************************
*/
void				*ft_malloc_exit(size_t size);
/*
** check_whitespaces.c
*/
int					check_whitespaces(char c);

/*
** free_char.c
*/
void				free_char(char **s);

/*
** free_dchar.c
*/
void				free_dchar(char ***tab);

/*
** ft_2eputendl.c
*/
void				ft_2eputendl(char *s1, char *s2);

/*
** ft_2eputendl_fd.c
*/
void				ft_2eputendl_fd(char *s1, char *s2, int fd);

/*
** ft_2eputstr.c
*/
void				ft_2eputstr(char *s1, char *s2);

/*
** ft_2putstr.c
*/
void				ft_2putstr(char const *s, char const *s2);

/*
** ft_2putstr_fd.c
*/
void				ft_2putstr_fd(char const *s, char const *s2, int fd);

/*
** ft_add_str_to_board.c
*/
char				**ft_add_str_to_board(char **tab, char *str);

/*
** ft_atoi.c
*/
int					ft_atoi(const char *str);

/*
** ft_bracket.c
*/
int					ft_bracket(char *str, int top, int a, char *stack);

/*
** ft_bracket_index.c
*/
int					ft_bracket_index(char *str, int top, int a, char *stack);

/*
** ft_bzero.c
*/
void				ft_bzero(void *s, size_t n);

/*
** ft_cswap.c
*/
void				ft_cswap(char *a, char *b);

/*
** ft_check_dquote.c
*/
int					ft_check_dquote(char *input);

/*
** ft_check_squote.c
*/
int					ft_check_squote(char *input);

/*
** ft_e2putstr.c
*/
void				ft_e2putstr(char const *s, char const *s2);

/*
** ft_eputendl.c
*/
void				ft_eputendl(char const *s);

/*
** ft_eputendl_fd.c
*/
void				ft_eputendl_fd(char const *s, int fd);

/*
** ft_eputstr.c
*/
void				ft_eputstr(char const *s);

/*
** ft_fputendl.c
*/
void				ft_fputendl(char **s);

/*
** ft_fputstr.c
*/
void				ft_fputstr(char **s);

/*
** ft_fputstr_s.c
*/
void				ft_fputstr_s(char **s);

/*
** ft_free_array.c
*/
void				ft_free_array(char **input);

/*
** ft_ipbackc.c
*/
int					ft_ipbackc(char *str, char c);

/*
** ft_ipbackws.c
*/
int					ft_ipbackws(char *str);

/*
** ft_ipfrontc.c
*/
int					ft_ipfrontc(char *str, char c);

/*
** ft_ipfrontws.c
*/
int					ft_ipfrontws(char *str);

/*
** ft_isalnum.c
*/
int					ft_isalnum(int c);

/*
** ft_isalpha.c
*/
int					ft_isalpha(int c);

/*
** ft_isascii.c
*/
int					ft_isascii(int c);

/*
** ft_isdigit.c
*/
int					ft_isdigit(int c);

/*
** ft_islower.c
*/
int					ft_islower(char c);

/*
** ft_isnum.c
*/
int					ft_isnum(int c);

/*
** ft_isprint.c
*/
int					ft_isprint(int c);

/*
** ft_isspace.c
*/
int					ft_isspace(char c);

/*
** ft_istrcpy.c
*/
char				*ft_istrcpy(char *dest, const char *src);

/*
** ft_itoa.c
*/
char				*ft_itoa(int n);

/*
** ft_lstadd.c
*/
void				ft_lstadd(t_list **alst, t_list *new);

/*
** ft_lstdel.c
*/
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));

/*
** ft_lstdelone.c
*/
void				ft_lstdelone(
	t_list **alst, void (*del)(void *, size_t));

/*
** ft_lstiter.c
*/
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));

/*
** ft_lstmap.c
*/
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

/*
** ft_lstnew.c
*/
t_list				*ft_lstnew(void const *content, size_t content_size);

/*
** ft_lstsize.c
*/
int					ft_lstsize(t_list *lst);

/*
** ft_ltoa.c
*/
char				*ft_ltoa(long long n);

/*
** ft_marge.c
*/
void				ft_marge(int m);

/*
** ft_memalloc.c
*/
void				*ft_memalloc(size_t size);

/*
** ft_memccpy.c
*/
void				*ft_memccpy(
	void *dst, const void *src, int c, size_t n);

/*
** ft_memchr.c
*/
void				*ft_memchr(const void *s, int c, size_t n);

/*
** ft_memcmp.c
*/
int					ft_memcmp(const void *s1, const void *s2, size_t n);

/*
** ft_memcpy.c
*/
void				*ft_memcpy(void *dst, const void *src, size_t n);

/*
** ft_memdel.c
*/
void				ft_memdel(void **ap);

/*
** ft_memicpy.c
*/
void				*ft_memicpy(void *dst, const void *src, size_t n);

/*
** ft_memmove.c
*/
void				*ft_memmove(void *dst, const void *src, size_t len);

/*
** ft_memset.c
*/
void				*ft_memset(void *b, int c, size_t len);

/*
** ft_mputendl.c
*/
void				ft_mputendl(char const *s, int m);

/*
** ft_mputstr.c
*/
void				ft_mputstr(char const *s, int m);

/*
** ft_mstrcpy.c
*/
char				*ft_mstrcpy(char *dest, const char *src);

/*
** ft_nbcword.c
*/
int					ft_nbcword(char *s, char c);

/*
** ft_nbword.c
*/
int					ft_nbword(char *s);

/*
** ft_nci.c
*/
int					ft_nci(int n);

/*
** ft_ncl.c
*/
int					ft_ncl(long long n);

/*
** ft_padding.c
*/
void				ft_padding(int padd);

/*
** ft_pbackc.c
*/
char				*ft_pbackc(char *str, char c);

/*
** ft_pbackws.c
*/
char				*ft_pbackws(char *str);

/*
** ft_pfrontc.c
*/
char				*ft_pfrontc(char *str, char c);

/*
** ft_pfrontws.c
*/
char				*ft_pfrontws(char *str);

/*
** ft_pstrback.c
*/
char				*ft_pstrback(char *str);

/*
** ft_pstrfront.c
*/
char				*ft_pstrfront(char *str);

/*
** ft_ptchar.c
*/
int					ft_ptchar(int c);

/*
** ft_ptchar_fd.c
*/
int					ft_ptchar_fd(int c, int fd);

/*
** ft_putchar.c
*/
void				ft_putchar(char c);

/*
** ft_putchar_fd.c
*/
void				ft_putchar_fd(char c, int fd);

/*
** ft_putendl.c
*/
void				ft_putendl(char const *s);

/*
** putendcol.c
*/
void				putendcol(char *str, char *color, char *colreset);

/*
** ft_putendl_fd.c
*/
void				ft_putendl_fd(char const *s, int fd);

/*
** ft_putlstback.c
*/
void				ft_putlstback(t_list **lst);

/*
** ft_putlstfront.c
*/
void				ft_putlstfront(t_list **lst);

/*
** ft_putnbr.c
*/
void				ft_putnbr(int n);

/*
** ft_putnbr_fd.c
*/
void				ft_putnbr_fd(int n, int fd);

/*
** ft_putstr.c
*/
void				ft_putstr(char const *s);

/*
** ft_putstr_fd.c
*/
void				ft_putstr_fd(char const *s, int fd);

/*
** ft_putstr_s.c
*/
void				ft_putstr_s(char const *s);

/*
** ft_split_whitespaces.c
*/
int					ft_nb_words(char *str);
int					ft_ln_w(char *str, int i);
char				**ft_split_whitespaces(char *str);

/*
** ft_splitws.c
*/
char				**ft_splitws(char const *s);

/*
** ft_sstrev.c
*/
char				**ft_sstrev(char **s, int c);

/*
** ft_strcat.c
*/
char				*ft_strcat(char *s1, const char *s2);

/*
** ft_strchr.c
*/
char				*ft_strchr(const char *s, int c);

/*
** ft_strclr.c
*/
char				*ft_strclr2(char *s);

/*
** ft_strcmp.c
*/
int					ft_strcmp(const char *s1, const char *s2);

/*
** ft_strcpy.c
*/
char				*ft_strcpy(char *dest, const char *src);

/*
** ft_strdel.c
*/
void				ft_strdel(char **as);

/*
** ft_strdup.c
*/
char				*ft_strdup(const char *s1);

/*
** ft_strequ.c
*/
int					ft_strequ(char const *s1, char const *s2);

/*
** ft_strev.c
*/
char				*ft_strev(char *s);

/*
** ft_striter.c
*/
void				ft_striter(char *s, void (*f)(char *));

/*
** ft_striteri.c
*/
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

/*
** ft_strjoin.c
*/
char				*ft_strjoin(char const *s1, char const *s2);

/*
** ft_strjoin_free.c
*/
char				*ft_strjoin_free(char *s1, char *s2);

/*
** ft_strjoin_one.c
*/
char				*ft_strjoin_one(char *s1, char c);

/*
** ft_strjoin_onef.c
*/
char				*ft_strjoin_onef(char *str, char c);

/*
** ft_strlcat.c
*/
size_t				ft_strlcat(
	char *dst, const char *src, size_t dstsize);

/*
** ft_strlen.c
*/
size_t				ft_strlen(const char *s);

/*
** ft_strmap.c
*/
char				*ft_strmap(char const *s, char (*f)(char));

/*
** ft_strmapi.c
*/
char				*ft_strmapi(
	char const *s, char (*f)(unsigned int, char));

/*
** ft_strncat.c
*/
char				*ft_strncat(char *s1, const char *s2, size_t n);

/*
** ft_strncmp.c
*/
int					ft_strncmp(const char *s1, const char *s2, size_t n);

/*
** ft_strncpy.c
*/
char				*ft_strncpy(char *dest, const char *src, size_t len);

/*
** ft_strnequ.c
*/
int					ft_strnequ(char const *s1, char const *s2, size_t n);

/*
** ft_strnew.c
*/
char				*ft_strnew(size_t size);

/*
** ft_strnstr.c
*/
char				*ft_strnstr(
	const char *haystack, const char *needle, size_t len);

/*
** ft_strrchr.c
*/
char				*ft_strrchr(const char *s, int c);

/*
** ft_strrev.c
*/
char				*ft_strrev(char *str);

/*
** ft_strsplit.c
*/
char				**ft_strsplit(char const *s, char c);

/*
** ft_strstr.c
*/
char				*ft_strstr(const char *haystack, const char *needle);

/*
** ft_strsub.c
*/
char				*ft_strsub(
	char const *s, unsigned int start, size_t len);

/*
** ft_strtrim.c
*/
char				*ft_strtrim(char const *s);

/*
** ft_swap.c
*/
void				ft_swap(int *a, int *b);

/*
** ft_tablen.c
*/
int					ft_tablen(char **environ);

/*
** ft_tolower.c
*/
int					ft_tolower(int c);

/*
** ft_toupper.c
*/
int					ft_toupper(int c);

/*
** get_next_line.c
*/
void				ft_free(void **ap);
int					get_next_line(int fd, char **line);

/*
** putendl_dchar.c
*/
void				putendl_dchar(char **s);

/*
** ft_is_space.c
*/
int					ft_is_space(char *input);

#endif
