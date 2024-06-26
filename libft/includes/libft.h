/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: requinch <requinch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:12:37 by requinch          #+#    #+#             */
/*   Updated: 2022/05/09 17:46:03 by requinch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define BUFFER_SIZE 500

typedef struct s_cmd
{
	char			*command;
	char			**arg;
	int				*spaces;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}				t_cmd;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

int				ft_abs(int i);
int				ft_strlen(const char *str);
int				ft_isprint(int c);
int				ft_isascii(int c);
int				ft_isalnum(int c);
int				ft_isdigit(int c);
int				ft_isinteger(char *str);
int				ft_isfloat(char *str);

int				ft_isalpha(int c);
int				ft_atoi(char *str);
double			ft_atof(char *str);
long double		ft_int_pow(long double nb, int pow);
int				ft_tolower(int c);
int				ft_toupper(int c);
char			*ft_strchr(const char *s, int c);

int				ft_integerternary(int cond, int t, int f);

char			*ft_strrchr(const char *s, int c);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strstr(char *str, char *to_find);
char			*ft_strcpy(char *src);

void			*ft_memset(void *s, int c, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);

void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);
char			*ft_strdup(const char *s);

char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
void			ft_putnbr_fd(int n, int fd);

char			**ft_split(char const *s, char c);
char			*ft_join(char **arg, t_cmd *cmd);

char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);

void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstadd_front(t_list **alst, t_list *new);
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstnew(void *content);
int				ft_lstsize(t_list *lst);

void			ft_lstdelone(t_list *lst, void (*del)(void*));
t_list			*ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));

int				ft_hexatoi(char *str, int j);
char			*ft_itohexa(int nb);

int				get_next_line(int fd, char **line);
char			*ft_strdup(const char *s);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
int				has_nl(char *str);

#endif
