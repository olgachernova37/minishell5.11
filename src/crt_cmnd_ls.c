/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crt_cmnd_ls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:38:44 by dtereshc          #+#    #+#             */
/*   Updated: 2025/11/04 13:26:48 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// returns pointer to the next command from t_input words
t_input	*move_ptr_cmnd(t_input *next_cmnd)
{
	if (next_cmnd == NULL)
		return (NULL);
	while (next_cmnd != NULL && next_cmnd->type != TOKEN_PIPE)
		next_cmnd = next_cmnd->next;
	if (next_cmnd != NULL && next_cmnd->type == TOKEN_PIPE)
		return (next_cmnd->next);
	return (NULL);
}

// rdrs fields inicialization
void	end_do_rdrs(t_cmnd *node, t_rdrs *rdr_node, t_rdrs *prev_node, int i)
{
	if (!node)
		exit(12);
	rdr_node->redir_type = *(node->argv_type[i]);
	rdr_node->filename = node->full_argv[i + 1];
	rdr_node->next = NULL;
	if (node->rdrs == NULL)
		node->rdrs = rdr_node;
	else
		prev_node->next = rdr_node;
	prev_node = rdr_node;
}

// setup of each cmnd node
t_cmnd	*setup_cmnd_node(t_cmnd *node, t_input *next_cmnd)
{
	int		size_argv;
	int		size;

	size_argv = count_cmnd_len_argv(next_cmnd);
	size = count_cmnd_len(next_cmnd);
	do_cmnd_array(next_cmnd, node, size_argv);
	do_full_cmnd_array(next_cmnd, node, size);
	do_cmnd_array_type(next_cmnd, node, size);
	do_rdrs(node);
	set_apnd_hered_pipe(node);
	return (node);
}

t_cmnd	*crt_cmnd_ls_lgc(int cmnd_qntt, t_cmnd *list,
		t_input *words)
{
	t_cmnd	*cmnd_node;
	t_cmnd	*prev_node;

	while (cmnd_qntt--)
	{
		cmnd_node = malloc(sizeof(t_cmnd));
		if (cmnd_node == NULL)
			exit(1);
		set_to_zero(cmnd_node);
		cmnd_node = setup_cmnd_node(cmnd_node, words);
		if (!list)
		{
			list = cmnd_node;
			prev_node = list;
		}
		else
		{
			prev_node->next = cmnd_node;
			prev_node = cmnd_node;
		}
		words = move_ptr_cmnd(words);
	}
	return (list);
}

// add free()
// main outter func
t_cmnd	*crt_cmnd_ls(t_input *words)
{
	int		cmnd_qntt;
	t_cmnd	*list;

	if (words == NULL)
		return (NULL);
	cmnd_qntt = count_cmnds(words);
	list = NULL;
	list = crt_cmnd_ls_lgc(cmnd_qntt, list, words);
	return (list);
}
