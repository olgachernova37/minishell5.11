/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:25:58 by dtereshc          #+#    #+#             */
/*   Updated: 2025/11/04 18:32:38 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//full file check is needed 

// eat U+00A0 (C2 A0) -> write ' ' and advance
static int	eat_nbsp(char *s, size_t *r, size_t *w, const unsigned char *p)
{
	if (p[0] != 0xC2 || p[1] != 0xA0)
		return (0);
	s[(*w)++] = ' ';
	*r += 2;
	return (1);
}

// eat U+200B (E2 80 8B) -> remove
static int	eat_zwsp(const unsigned char *p, size_t *r)
{
	if (p[0] != 0xE2 || p[1] != 0x80 || p[2] != 0x8B)
		return (0);
	*r += 3;
	return (1);
}

// write char, mapping ASCII control whitespace to ' ' 
static void	put_norm_char(char *s, size_t r, size_t *w)
{
	unsigned char	c;

	c = (unsigned char)s[r];
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f')
		c = ' ';
	s[(*w)++] = (char)c;
}

void	normalize_input_inplace(char *s)
{
	size_t	r;
	size_t	w;

	if (!s)
		return ;
	r = 0;
	w = 0;
	while (s[r])
	{
		if (eat_nbsp(s, &r, &w, (unsigned char *)s + r))
			continue ;
		if (eat_zwsp((unsigned char *)s + r, &r))
			continue ;
		if ((unsigned char)s[r] == '\r')
		{
			r++;
			continue ;
		}
		put_norm_char(s, r, &w);
		r++;
	}
	s[w] = '\0';
}

int	is_shell_space(unsigned char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v'
		|| c == '\f');
}
