/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:48 by dtereshc          #+#    #+#             */
/*   Updated: 2025/11/03 15:57:27 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_quote_state_pipe(char c, int *in_q)
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

static int	check_pipe_after_spaces(char *input, int *i)
{
	*i += 1;
	*i += skip_spaces(&input[*i]);
	if (input[*i] == '\0' || (input[*i] == '|' && input[*i + 1] != '|'))
		return (1);
	return (0);
}

static int	validate_pipes_in_loop(char *input, int start_pos)
{
	int	in_q;
	int	i;

	in_q = 0;
	i = start_pos;
	while (input[i])
	{
		update_quote_state_pipe(input[i], &in_q);
		if (!in_q && input[i] == '|' && input[i + 1] != '|')
		{
			if (check_pipe_after_spaces(input, &i))
				return (1);
			continue ;
		}
		i++;
	}
	return (0);
}

int	has_invalid_pipe(char *input)
{
	int	i;

	i = skip_spaces(input);
	if (input[i] == '|' && input[i + 1] != '|')
		return (1);
	return (validate_pipes_in_loop(input, i));
}

int	process_redirection_in_loop(char *input, int *i, t_redir_context *ctx)
{
	if (!ctx->in_q && is_redir_char(input[*i]))
		return (process_found_redirection(input, i, ctx));
	return (0);
}
