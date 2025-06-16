/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:15:26 by tbatis            #+#    #+#             */
/*   Updated: 2025/06/09 22:31:41 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);

// String functions
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcat(char *dest, const char *src);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_str_append(char *dst, const char *src);
char	*ft_strrchr(const char *s, int c);
void	*ft_calloc(size_t count, size_t size);
bool	ft_str_is_num(char *str);

// Memory functions
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t len);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

// Conversion functions
int		ft_atoi(const char *str);
long	ft_atol(const char *str);

// additional functions
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	**ft_split(char const *s, char c);
void	free_ft_split_array(char **string_array);
int		ft_arraylen(char **array);

// printf
int		ft_putchar(char c);
int		ft_printf(const char *format, ...);
int		ft_putnbr(unsigned int num);
bool	printf_print_num(const char c, int *chars_printed, va_list args);
bool	printf_print_unum(const char c, int *chars_printed, va_list args);
void	ft_printint(int number);

// print str
bool	printf_print_percent(const char c, int *chars_printed);
bool	printf_print_char(const char c, int *chars_printed, va_list args);
bool	printf_print_string(const char c, int *chars_printed, va_list args);

// minilib
void	decimal_to_hex(unsigned long int decimal, char hexa_number[200],
			char *radix);
int		ft_putnbr_base(unsigned long int nbr, bool capital);

#endif
