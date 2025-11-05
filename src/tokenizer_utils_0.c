/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_0.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 00:41:29 by dtereshc          #+#    #+#             */
/*   Updated: 2025/11/04 17:40:15 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_len_type_qts	*tk_out_appnd(char *input, t_len_type_qts *ltq)
{
	char	*tmp;

	if (!input || !ltq)
		return (NULL);
	tmp = input;
	ltq->len = 1;
	ltq->qts = 0;
	ltq->type = TOKEN_RDR_OUT;
	if (*(++tmp) == '>')
	{
		ltq->len += 1;
		ltq->type = TOKEN_APPND;
	}
	return (ltq);
}

// new if()
t_len_type_qts	*tk_in_here(char *input, t_len_type_qts *ltq)
{
	char	*tmp;

	if (!input || !ltq)
		return (NULL);
	tmp = input;
	ltq->len = 1;
	ltq->qts = 0;
	ltq->type = TOKEN_RDR_IN;
	if (*(++tmp) == '<')
	{
		ltq->len += 1;
		ltq->type = TOKEN_HERE;
	}
	return (ltq);
}

// new if()
t_len_type_qts	*tk_pipe(t_len_type_qts *ltq)
{
	if (!ltq)
		return (NULL);
	ltq->len = 1;
	ltq->type = TOKEN_PIPE;
	ltq->qts = 0;
	return (ltq);
}

// new if()
void	end_do_node(t_len_type_qts *ltq, t_input *new_node, char *res)
{
	if (!ltq || !new_node || !res)
		return ;
	new_node->word = res;
	new_node->next = NULL;
	if (ltq->qts)
		new_node->type = TOKEN_COMPLEX;
	else
		new_node->type = ltq->type;
}
