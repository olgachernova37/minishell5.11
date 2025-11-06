/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:34:37 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/06 15:08:47 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

# define STDERR_FD 2
# define STDOUT_FD 1

int	ft_printf(const char *format, ...);
int	ft_fprintf(int fd, const char *format, ...);
int	print_specifier(char symbol, va_list args);
int	print_char(int c);
int	print_str(char *str);
int	print_nbr(int num);
int	unsigned_print_nbr(unsigned int num);
int	print_address(void *ptr);
int	print_hexadecimal(unsigned int nbr, char symbol);
int	print_hexadecimal_fd(unsigned long nbr, char symbol, int fd);
int	print_char_fd(int c, int fd);
int	print_str_fd(char *str, int fd);
int	print_nbr_fd(int num, int fd);
int	unsigned_print_nbr_fd(unsigned int num, int fd);
int	print_address_fd(void *ptr, int fd);
int	print_specifier_fd(char symbol, va_list args, int fd);

// int	print_format(char character, va_list ap);
// int	print_hexadecimal(char character, unsigned int num);
// int	print_hex_digit(unsigned char digit);

#endif
