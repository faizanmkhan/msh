/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:15:36 by korzecho          #+#    #+#             */
/*   Updated: 2024/03/03 23:05:54 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdint.h>

int				ft_isalpha(int c);
int				ft_isdigit(int arg);
int				ft_isalnum(int arg);
int				ft_isascii(int arg);
int				ft_isprint(int arg);
int				ft_strlen(char *arg);
int				ft_toupper(int ch);
int				ft_tolower(int ch);
int				ft_strncmp( const char *str1, const char *str2, unsigned int n);
int				ft_memcmp(const void *str1, const void *str2, unsigned int n);
int				ft_atoi(const char *str);
unsigned int	ft_strlcpy(char *dest, const char *src, unsigned int size);
unsigned int	ft_strlcat(char *dst, const char *src, unsigned int size);
char			*ft_strdup(const char *str);
char			*ft_itoa(int n);
char			**ft_split(char const *s, char c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strchr(const char *str, int c);
char			*ft_strrchr(const char *str, int c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strnstr(const char *big, const char *sml, unsigned int len);
void			*ft_memchr(const void *str, int c, unsigned int n);
void			*ft_memset(void *ptr, int value, unsigned int num);
void			*ft_memcpy(void *dst, const void *src, unsigned int n);
void			ft_bzero(void *s, unsigned int n);
void			*ft_memmove(void *dest, const void *src, unsigned int n);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			*ft_calloc(size_t nmemb, size_t size);
#endif