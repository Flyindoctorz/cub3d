/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:44:11 by zakchouc          #+#    #+#             */
/*   Updated: 2025/06/02 15:02:37 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# ifdef __linux__
#  include "bsd/string.h"
# endif /* __linux__ */

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void				ft_lstadd_back(t_list **lst, t_list *new);

void				ft_lstadd_front(t_list **lst, t_list *new);

void				ft_lstclear(t_list **lst, void (*del)(void *));

void				ft_lstdelone(t_list *lst, void (*del)(void *));

void				ft_lstiter(t_list *lst, void (*f)(void *));

t_list				*ft_lstlast(t_list *lst);

t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

t_list				*ft_lstnew(void *content);

int					ft_lstsize(t_list *lst);

int					ft_atoi(const char *nptr);

void				ft_bzero(void *s, size_t n);

void				*ft_calloc(size_t nmemb, size_t size);

int					ft_isalnum(int c);

int					ft_isalpha(int c);

int					ft_isascii(int c);

int					ft_isdigit(int c);

int					ft_isprint(int c);

char				*ft_itoa(int n);

void				*ft_memchr(const void *s, int c, size_t n);

int					ft_memcmp(const void *s1, const void *s2, size_t n);

void				*ft_memcpy(void *dest, const void *src, size_t size);

void				*ft_memmove(void *dest, const void *src, size_t size);

void				*ft_memset(void *ptr, int value, size_t count);

void				ft_putchar_fd(char c, int fd);

void				ft_putendl_fd(char *s, int fd);

void				ft_putnbr_fd(int n, int fd);

void				ft_putnbr_printf_fd(int n, int fd, int *count);

void				ft_putstr_fd(char *s, int fd);

char				**ft_split(char const *s, char c);

char				*ft_strcat(char *dest, const char *src);

char				*ft_strchr(const char *s, int c);

char				*ft_strcpy(char *dest, const char *src);

char				*ft_strdup(const char *s);

void				ft_striteri(char *s, void (*f)(unsigned int, char *));

char				*ft_strjoin(char const *s1, char const *s2);

size_t				ft_strlcat(char *dest, const char *src, size_t size);

size_t				ft_strlcpy(char *dst, const char *src, size_t size);

size_t				ft_strlen(const char *str);

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int					ft_strcmp(const char *s1, const char *s2);

int					ft_strncmp(const char *first, const char *second,
						size_t length);

char				*ft_strndup(const char *s, size_t n);

char				*ft_strnjoin(char *s1, char *s2, size_t n);

char				*ft_strnstr(const char *big, const char *little,
						size_t len);

char				*ft_strrchr(const char *s, int c);

char				**ft_strtok(const char *str, const char *delimiters);

char				*ft_strtrim(char const *s1, char const *set);

char				*ft_substr(char const *s, unsigned int start, size_t len);

int					ft_tolower(int c);

int					ft_toupper(int c);

int					ft_isspace(int c);

#endif /* LIBFT_H */
