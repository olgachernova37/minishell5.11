/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:48 by dtereshc          #+#    #+#             */
/*   Updated: 2025/11/03 15:59:29 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_quote_state(char c, int *in_q)
{
	if (c == 34 && !(*in_q))
		*in_q = 1;
	else if (c == 39 && !(*in_q))
		*in_q = 2;
	else if (c == 34 && *in_q == 1)
		*in_q = 0;
	else if (c == 39 && *in_q == 2)
		*in_q = 0;
}

int	check_redirection_end(char *input, int i, char *bad_char, int *is_newline)
{
	if (input[i] == '\0')
	{
		*is_newline = 1;
		*bad_char = '\0';
		return (1);
	}
	if (input[i] == '|' && input[i + 1] != '|')
	{
		*bad_char = '|';
		return (1);
	}
	if (is_redir_char(input[i]))
	{
		*bad_char = input[i];
		return (1);
	}
	return (0);
}

int	check_leading_redirection(char *input, char *bad_char, int *is_newline)
{
	int	i;
	int	op_len;

	i = skip_spaces(input);
	if (input[i] && is_redir_char(input[i]))
	{
		op_len = 1;
		if (input[i + 1] == input[i])
			op_len = 2;
		i += op_len;
		i += skip_spaces(&input[i]);
		if (input[i] == '\0')
		{
			*is_newline = 1;
			*bad_char = '\0';
			return (1);
		}
	}
	return (0);
}

int	process_found_redirection(char *input, int *i, t_redir_context *ctx)
{
	int	op_len;

	op_len = 1;
	if (input[*i + 1] == input[*i])
		op_len = 2;
	*i += op_len;
	*i += skip_spaces(&input[*i]);
	if (check_redirection_end(input, *i, ctx->bad_char, ctx->is_newline))
		return (1);
	return (2);
}

int	validate_redirections_loop(char *input, char *bad_char, int *is_newline)
{
	int				i;
	int				result;
	t_redir_context	ctx;

	ctx.bad_char = bad_char;
	ctx.is_newline = is_newline;
	ctx.in_q = 0;
	i = 0;
	while (input[i])
	{
		update_quote_state(input[i], &ctx.in_q);
		result = process_redirection_in_loop(input, &i, &ctx);
		if (result == 1)
			return (1);
		if (result == 2)
			continue ;
		i++;
	}
	return (0);
}
