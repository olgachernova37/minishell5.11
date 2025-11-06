/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:00:00 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/06 15:09:30 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hexadecimal_fd(unsigned long nbr, char symbol, int fd)
{
	int		count;
	char	*hex_base;

	count = 0;
	if (symbol == 'X')
		hex_base = "0123456789ABCDEF";
	else
		hex_base = "0123456789abcdef";
	if (nbr == 0)
		return (write(fd, "0", 1));
	if (nbr >= 16)
		count += print_hexadecimal_fd(nbr / 16, symbol, fd);
	count += write(fd, &hex_base[nbr % 16], 1);
	return (count);
}

int	print_char_fd(int c, int fd)
{
	return (write(fd, &c, 1));
}

int	print_str_fd(char *str, int fd)
{
	int	count;

	count = 0;
	if (!str)
		str = "(null)";
	while (*str)
	{
		count += write(fd, str, 1);
		str++;
	}
	return (count);
}
