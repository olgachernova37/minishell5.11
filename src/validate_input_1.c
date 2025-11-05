/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtereshc <dtereshc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:48 by dtereshc          #+#    #+#             */
/*   Updated: 2025/11/03 20:20:46 by dtereshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_backslash(char *input)
{
	int	in_q;

	in_q = 0;
	while (*input != '\0')
	{
		if (*input == 34 && !in_q)
			in_q = 1;
		else if (*input == 39 && !in_q)
			in_q = 2;
		else if (*input == 34 && in_q == 1)
			in_q = 0;
		else if (*input == 39 && in_q == 2)
			in_q = 0;
		if (*input == 92 && !in_q)
			return (1);
		input++;
	}
	return (0);
}

int	has_simocolon(char *input)
{
	int	in_q;

	in_q = 0;
	while (*input != '\0')
	{
		if (*input == 34 && !in_q)
			in_q = 1;
		else if (*input == 39 && !in_q)
			in_q = 2;
		else if (*input == 34 && in_q == 1)
			in_q = 0;
		else if (*input == 39 && in_q == 2)
			in_q = 0;
		if (*input == 59 && !in_q)
			return (1);
		input++;
	}
	return (0);
}

int	has_double_and_or_pipe(char *input)
{
	int	in_q;

	in_q = 0;
	while (*input != '\0')
	{
		if (*input == 34 && !in_q)
			in_q = 1;
		else if (*input == 39 && !in_q)
			in_q = 2;
		else if (*input == 34 && in_q == 1)
			in_q = 0;
		else if (*input == 39 && in_q == 2)
			in_q = 0;
		if (!in_q && (((*input == 38 && *(input + 1) == 38)) || ((*input == 124)
				&& *(input + 1) == 124)))
			return (1);
		input++;
	}
	return (0);
}

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}

int	is_redir_char(char c)
{
	return (c == '<' || c == '>');
}
