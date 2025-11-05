/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:11:33 by dtereshc          #+#    #+#             */
/*   Updated: 2025/11/04 18:31:25 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// every uninquoted qutes should be skipped
// probably should be added free(words) if (words != NULL)
t_input	*do_node(t_len_type_qts *ltq, char *input)
{
	int				i;
	char			*res;
	t_input			*new_node;
	t_quote_state	*state;

	i = 0;
	state = NULL;
	new_node = malloc(sizeof(t_input));
	if (!new_node || !input)
		return (NULL);
	res = malloc(sizeof(char) * (ltq->len - ltq->qts + 1));
	if (res == NULL)
		return (do_node_clear(new_node)); // free() check afterall
	while (input && i < (ltq->len - ltq->qts))
	{
		state = dtct_inquotes(*input);
		if ((state->inquotes && state->type == *input) || state->closed)
			input++;
		else
			res[i++] = *input++;
	}
	res[i] = '\0';
	end_do_node(ltq, new_node, res);
	reset_state_sttc(state);
	return (new_node);
}

void	add_node(t_input **words, t_input *new_word)
{
	t_input	*tmp;

	if (!words || !new_word)
		return ;
	if (*words == NULL)
	{
		*words = new_word;
		return ;
	}
	tmp = *words;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_word;
}

int	creat_tokenz(char *input, t_input **words)
{
	t_len_type_qts	*ltq;
	int				cnsmd;

	ltq = malloc(sizeof(t_len_type_qts));
	if (!ltq)
		exit(1);
	ltq->qts = 0;
	ltq->len = 0;
	ltq->type = -1;
	if (*input == '|')
		add_node(words, do_node(tk_pipe(ltq), input));
	else if (*input == '>')
		add_node(words, do_node(tk_out_appnd(input, ltq), input));
	else if (*input == '<')
		add_node(words, do_node(tk_in_here(input, ltq), input));
	else
		add_node(words, do_node(tk_word(input, ltq), input));
	cnsmd = ltq->len;
	free(ltq);
	return (cnsmd);
}

t_input	*tokenize(t_input *words, char *input)
{
	int	res;

	res = 0;
	if (!input)
		return (NULL);
	while (*input)
	{
		if (!is_shell_space((unsigned char)*input))
		{
			res = creat_tokenz(input, &words);
			input += res;
		}
		else
			input++;
	}
	return (words);
}
