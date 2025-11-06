/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:00:00 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/06 15:06:41 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_nbr_fd(int num, int fd)
{
	int		count;
	char	c;

	count = 0;
	if (num == -2147483648)
		return (write(fd, "-2147483648", 11));
	if (num < 0)
	{
		count += write(fd, "-", 1);
		num = -num;
	}
	if (num >= 10)
		count += print_nbr_fd(num / 10, fd);
	c = (num % 10) + '0';
	count += write(fd, &c, 1);
	return (count);
}

int	unsigned_print_nbr_fd(unsigned int num, int fd)
{
	int		count;
	char	c;

	count = 0;
	if (num >= 10)
		count += unsigned_print_nbr_fd(num / 10, fd);
	c = (num % 10) + '0';
	count += write(fd, &c, 1);
	return (count);
}

int	print_address_fd(void *ptr, int fd)
{
	unsigned long	addr;
	int				count;

	count = 0;
	if (!ptr)
		return (write(fd, "(nil)", 5));
	addr = (unsigned long)ptr;
	count += write(fd, "0x", 2);
	if (addr == 0)
		return (count + write(fd, "0", 1));
	count += print_hexadecimal_fd(addr, 'x', fd);
	return (count);
}

int	print_specifier_fd(char symbol, va_list args, int fd)
{
	int	count;

	count = 0;
	if (symbol == 'c')
		count += print_char_fd(va_arg(args, int), fd);
	else if (symbol == 's')
		count += print_str_fd(va_arg(args, char *), fd);
	else if (symbol == 'p')
		count += print_address_fd(va_arg(args, void *), fd);
	else if (symbol == 'd' || symbol == 'i')
		count += print_nbr_fd(va_arg(args, int), fd);
	else if (symbol == 'u')
		count += unsigned_print_nbr_fd(va_arg(args, unsigned int), fd);
	else if (symbol == 'x' || symbol == 'X')
		count += print_hexadecimal_fd(va_arg(args, unsigned int), symbol, fd);
	else if (symbol == '%')
		count += write(fd, "%", 1);
	else
		count += write(fd, &symbol, 1);
	return (count);
}

int	ft_fprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		sum_of_printf;

	sum_of_printf = 0;
	va_start(args, format);
	while (format && *format)
	{
		if (*format == '%')
		{
			sum_of_printf += print_specifier_fd(*(++format), args, fd);
		}
		else
			sum_of_printf += write(fd, format, 1);
		format++;
	}
	va_end(args);
	return (sum_of_printf);
}
