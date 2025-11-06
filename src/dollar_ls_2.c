/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_ls_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:54:13 by dtereshc          #+#    #+#             */
/*   Updated: 2025/11/06 13:12:52 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_xtnd	*handle_dollar_expansion(char **input, t_env **env,
		t_quote_state *st)
{
	t_xtnd	*xtnd_node;

	if (**input == '$' && *(*input + 1) && (st->type == '"' || st->type == 0)
		&& (is_delimiter(*(*input + 1)) || !(is_delimiter(*(*input + 1)))))
	{
		xtnd_node = crt_xtnd_logic(*input + 1, env, st);
		return (xtnd_node);
	}
	return (NULL);
}

static t_xtnd	*handle_dollar_quote(char **input, t_quote_state *st)
{
	t_xtnd	*xtnd_node;

	if (**input == '$' && st->type == 0 && (*(*input + 1) == '\'' || *(*input
				+ 1) == '"'))
	{
		xtnd_node = pst_q(*input + 2);
		return (xtnd_node);
	}
	return (NULL);
}

static int	process_input_char(char **input, t_env **env, t_xtnd **head)
{
	t_quote_state	*st;
	t_xtnd			*xtnd_node;

	st = dtct_inquotes(**input);
	if (!st)
		exit(40);
	xtnd_node = handle_dollar_expansion(input, env, st);
	if (xtnd_node)
	{
		connect_nodes(head, xtnd_node);
	}
	xtnd_node = handle_dollar_quote(input, st);
	if (xtnd_node)
	{
		connect_nodes(head, xtnd_node);
	}
	return (0);
}

t_xtnd	*crt_xtnd_ls(char *input, t_env **env)
{
	t_xtnd	*head;

	head = NULL;
	if (!input || !env)
		return (NULL);
	while (*input)
	{
		process_input_char(&input, env, &head);
		input++;
	}
	return (head);
}
