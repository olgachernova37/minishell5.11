/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:37:46 by dt                #+#    #+#             */
/*   Updated: 2025/11/04 21:12:03 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// needed to be checked
void	*do_node_clear(t_input *new_node)
{
	free(new_node);
	return (NULL);
}

// in rdrs frees only  nodes of th elist buts its field
// fields will be freed within free_t_input()
// because it just copied by referenc
void	free_rdrs(t_rdrs *rdrs)
{
	t_rdrs	*prev;

	if (!rdrs)
		return ;
	while (rdrs)
	{
		prev = rdrs;
		rdrs = rdrs->next;
		free(prev);
	}
}

// just frees array of pointers and the head of it
void	free_full_argv(t_cmnd *cmnd_node)
{
	if (!cmnd_node || !cmnd_node->full_argv)
		return ;
	free(cmnd_node->full_argv);
	cmnd_node->full_argv = NULL;
}

// just frees array of pointers and the head of it
// but *argv просто присвоены по референсу из t_input
// so free(t_input) is needed here
void	free_argv_head(t_cmnd *cmnd_node)
{
	if (!cmnd_node || !cmnd_node->argv)
		return ;
	free(cmnd_node->argv);
	cmnd_node->argv = NULL;
}

void	free_cmnd_ls(t_cmnd **cmnd, t_input **words)
{
	t_cmnd	*nxt;
	t_cmnd	*cur_node;

	if (!cmnd || !*cmnd)
		return ;
	cur_node = *cmnd;
	while (cur_node)
	{
		nxt = cur_node->next;
		free_argv_head(cur_node);
		free_full_argv(cur_node);
		free_argv_type(cur_node);
		free_rdrs(cur_node->rdrs);
		free(cur_node);
		cur_node = nxt;
	}
	*cmnd = NULL;
	if (words)
		free_t_input(words);
}
