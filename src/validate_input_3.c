/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:48 by dtereshc          #+#    #+#             */
/*   Updated: 2025/11/03 15:43:28 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_invalid_redirections(char *input, char *bad_char, int *is_newline)
{
	if (!input)
		return (0);
	*is_newline = 0;
	if (check_leading_redirection(input, bad_char, is_newline))
		return (1);
	return (validate_redirections_loop(input, bad_char, is_newline));
}

static bool	validate_basic_syntax(char *input)
{
	if (has_unclosed_quotes(input))
		return (drop_false("Minishell:  syntax error: unclosed quotes"));
	if (has_backslash(input))
		return (drop_false("Minishell: syntax error: unexpected '\\'"));
	if (has_simocolon(input))
		return (drop_false("Minishell: syntax error: unexpected ';'"));
	if (has_double_and_or_pipe(input))
		return (drop_false("Minishell: syntax error: unexpected '&&'or'||'"));
	if (has_invalid_pipe(input))
		return (drop_false("Minishell: syntax error: unexpected '|'"));
	return (true);
}

static bool	handle_redirection_error(char bad, int is_newline)
{
	char	msg[64];
	int		n;

	if (is_newline)
		return (drop_false("Minishell: syntax error: unexpected 'newline'"));
	else
	{
		n = snprintf(msg, sizeof(msg),
				"Minishell: syntax error: unexpected '%c'", bad);
		(void)n;
		return (drop_false(msg));
	}
}

static bool	validate_redirections(char *input)
{
	char	bad;
	int		is_newline;
	int		rv;

	rv = has_invalid_redirections(input, &bad, &is_newline);
	if (rv)
		return (handle_redirection_error(bad, is_newline));
	return (true);
}

bool	validate_input(char *input)
{
	if (!input)
		return (false);
	if (!validate_basic_syntax(input))
		return (false);
	return (validate_redirections(input));
}
