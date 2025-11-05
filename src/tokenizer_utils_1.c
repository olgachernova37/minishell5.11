/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 00:39:29 by dtereshc          #+#    #+#             */
/*   Updated: 2025/11/04 15:41:21 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	calc_len(t_input *new_word)
{
	int	len;

	len = 0;
	while (new_word->word[len] != '\0')
		len++;
	return (len);
}

// marks if the pointer is within quotes or out of them
t_quote_state	*dtct_inquotes(char cr)
{
	static t_quote_state	chr = {0, 0, 0, 0};

	if (cr == '\0')
		chr = (t_quote_state){0, 0, 0, 0};
	if (chr.new_pair)
		chr.new_pair = 0;
	if ((cr == '\'' || cr == '"'))
	{
		if (!chr.inquotes)
		{
			chr.type = cr;
			chr.closed = 0;
			chr.inquotes = 1;
			chr.new_pair = 1;
		}
		else if (cr == chr.type)
		{
			chr.type = 0;
			chr.closed = 1;
			chr.inquotes = 0;
		}
	}
	else if (chr.closed)
		chr.closed = 0;
	return (&chr);
}

// if > 0 is complex ==> returns how many ', "
// outter(that shouldnt be printed) are within one word
int	is_complex_wrd(t_len_type_qts *ltq, char *input)
{
	int				i;
	int				q;
	t_quote_state	*state;

	i = 0;
	q = 0;
	while (i < ltq->len && input[i])
	{
		state = dtct_inquotes(input[i++]);
		if (state->new_pair)
			q += 2;
	}
	reset_state_sttc(state);
	return (q);
}

t_len_type_qts	*tk_word(char *input, t_len_type_qts *ltq)
{
	t_quote_state	*state;
	char			*rst_input;

	rst_input = input;
	while (*input)
	{
		state = dtct_inquotes(*input);
		if ((is_shell_space((unsigned char)*input) || *input == '>'
				|| *input == '<' || *input == '|') && !state->inquotes)
			break ;
		ltq->len++;
		input++;
	}
	input = rst_input;
	reset_state_sttc(state);
	ltq->qts = is_complex_wrd(ltq, input);
	if (ltq->qts)
		ltq->type = TOKEN_COMPLEX;
	else
		ltq->type = TOKEN_WORD;
	return (ltq);
}
