/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:39:52 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/01 16:36:59 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
		while (i < n)
		{
			dest[i] = '\0';
			i++;
		}
		return (dest);
	}
	return (dest);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*o_dest;
	unsigned char	*o_src;

	if (!dest || !src)
		return (NULL);
	o_dest = (unsigned char *)dest;
	o_src = (unsigned char *)src;
	if (dest == (void *)0 && src == (void *)0)
	{
		return (dest);
	}
	while (n > 0)
	{
		*(o_dest++) = *(o_src++);
		n--;
	}
	return (dest);
}
