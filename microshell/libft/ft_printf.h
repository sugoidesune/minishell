/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:15:26 by tbatis            #+#    #+#             */
/*   Updated: 2025/03/05 16:39:58 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdbool.h>
# include <unistd.h>

int		ft_printf(const char *format, ...);
int		ft_putnbr(unsigned int num);
bool	printf_print_num(const char c, int *chars_printed, va_list args);
bool	printf_print_unum(const char c, int *chars_printed, va_list args);

// print str
bool	printf_print_percent(const char c, int *chars_printed);
bool	printf_print_char(const char c, int *chars_printed, va_list args);
bool	printf_print_string(const char c, int *chars_printed, va_list args);

//minilib
void	decimal_to_hex(unsigned long int decimal, char hexa_number[200],
			char *radix);
int		ft_putnbr_base(unsigned long int nbr, bool capital);

#endif
