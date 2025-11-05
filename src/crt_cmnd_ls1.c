/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crt_cmnd_ls1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:38:44 by dtereshc          #+#    #+#             */
/*   Updated: 2025/11/04 21:06:43 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_rdrs	*create_rdr_node(t_cmnd *node, int i)
{
	t_rdrs	*rdr_node;

	rdr_node = malloc(sizeof(t_rdrs));
	if (!rdr_node)
		exit(1);
	rdr_node->redir_type = *(node->argv_type[i]);
	rdr_node->filename = node->full_argv[i + 1];
	rdr_node->next = NULL;
	return (rdr_node);
}

static void	add_rdr_to_list(t_cmnd *node, t_rdrs *rdr_node, t_rdrs **prev_node)
{
	if (node->rdrs == NULL)
		node->rdrs = rdr_node;
	else
		(*prev_node)->next = rdr_node;
	*prev_node = rdr_node;
}

static int	process_redirection(t_cmnd *node, int i, t_rdrs **prev_node)
{
	t_rdrs	*rdr_node;

	if (!(node->argv_type[i + 1]))
		return (-1);
	rdr_node = create_rdr_node(node, i);
	add_rdr_to_list(node, rdr_node, prev_node);
	return (i + 2);
}

void	do_rdrs(t_cmnd *node)
{
	t_rdrs	*prev_node;
	int		i;
	int		next_i;

	i = 0;
	prev_node = NULL;
	while (node->full_argv[i])
	{
		if (*(node->argv_type[i]) >= TOKEN_RDR_IN
			&& *(node->argv_type[i]) <= TOKEN_HERE)
		{
			next_i = process_redirection(node, i, &prev_node);
			if (next_i == -1)
				break ;
			i = next_i;
			continue ;
		}
		i++;
	}
}
