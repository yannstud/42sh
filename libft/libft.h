/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 00:40:27 by slegros           #+#    #+#             */
/*   Updated: 2018/05/20 17:20:04 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

# define BUFF_SIZE 300

# define BLK "\x1B[30m"
# define RED "\x1B[31m"
# define GRN "\x1B[32m"
# define YEL "\x1B[33m"
# define BLU "\x1B[34m"
# define MAG "\x1B[35m"
# define CYN "\x1B[36m"
# define WHT "\x1B[37m"
# define BBLK "\x1B[90m"
# define BRED "\x1B[91m"
# define BGRN "\x1B[92m"
# define BYEL "\x1B[93m"
# define BBLU "\x1B[94m"
# define BMAG "\x1B[95m"
# define BCYN "\x1B[96m"
# define BWHT "\x1B[97m"
# define BOLD "\x1B[1m"
# define ITLC "\x1B[3m"
# define UNDE "\x1B[4m"
# define REVE "\x1B[7m"
# define RESET "\x1B[0m"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_brk
{
	int				cursh;
	int				subsh;
	int				quote;
	int				dquote;
	int				bquote;
}					t_brk;

char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, const char *src, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strdup(const char *s);
size_t				ft_strlen(const char *s);
char				*ft_strstr(const char *str1, const char *str2);
char				*ft_strnstr(const char *str1, const char *str2, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_bzero(void *s, size_t n);
char				*ft_strnew(size_t size);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char*s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
char				*ft_itoa(int n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				**ft_strsplit(char const *s, char c);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					ft_strichr(const char *s, int c);
int					ft_strirchr(const char *s, int c);
char				*ft_strjoinfree(char const *s1, char const *s2, int mode);
char				*ft_strsubf(char const *s, unsigned int start, size_t len);
int					ft_isspace(char c);
int					ft_isneg(int c);
int					ft_toabs(int c);
int					ft_pgcd(int a, int b);
char				**ft_strsplitspc(char const *s);
int					get_next_line(const int fd, char **line);
char				**ft_dbarrnew(int nb);
void				ft_dbarrprint(char **dbarr);
void				ft_dbarrprint_fd(char **dbarr, int fd);
int					ft_dbarrlen(char **dbarr);
char				**ft_dbarrdup(char **o_array);
char				**ft_dbarr_add(char **array, char *content);
char				**ft_dbarr_del(char **array, int index);
char				**ft_dbarr_edit(char **array, char *content, int i);
char				**ft_dbarrjoin(char **dbarr1, char **dbarr2);
char				**ft_dbarrjoinfree(char **dbarr1, char **dbarr2, int mode);
char				**ft_dbarr_free(char **array);
char				*ft_dbarrtostr(char **dbarr, char c);
void				ft_putnbrendl(int n);
void				ft_putstr_bdr(char const *s, char bdr);
void				ft_putstr_bdr_fd(char const *s, char bdr, int fd);
void				ft_putnbr_bdr(int n, char bdr);
void				ft_putnbr_bdr_fd(int n, char bdr, int fd);
void				ft_putnbrendl_fd(int n, int fd);
int					ft_strnbc(char *str, char c);
int					ft_onlyspc(char *str);
void				ft_putstr_col(char *str, char *col);
void				ft_putstr_col_fd(char *str, char *col, int fd);
void				ft_putendl_col(char *str, char *col);
void				ft_putendl_col_fd(char *str, char *col, int fd);
void				ft_putnbr_col(int nb, char *col);
void				ft_putnbr_col_fd(int nb, char *col, int fd);
void				ft_putnbrendl_col(int nb, char *col);
void				ft_putnbrendl_col_fd(int nb, char *col, int fd);
void				ft_putchar_col(char c, char *col);
void				ft_putchar_col_fd(char c, char *col, int fd);
char				*ft_strinsert(char *s1, char c, int place);
char				*ft_strrem(char *s1, int place);
int					ft_nbrlen(int nb);
int					ft_inbrk(char *str, int index);
int					ft_strnoreadable(char *str);
char				*ft_strdupf(char *str, char *tmp);
int					ft_dbarrnbstr(char **dbarr, char *str);
int					ft_dbarrichr(char **dbarr, char *str);
int					ft_dbarrirchr(char **dbarr, char *str);
void				ft_slip(int i);
int					ft_stristr(char *str1, char *str2);

#endif
