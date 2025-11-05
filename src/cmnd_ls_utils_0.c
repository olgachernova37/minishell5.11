/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmnd_ls_utils_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:31:02 by dtereshc          #+#    #+#             */
/*   Updated: 2025/11/03 16:19:46 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_to_zero(t_cmnd *cmnd_node)
{
	cmnd_node->argv = NULL;
	cmnd_node->full_argv = NULL;
	cmnd_node->argv_type = NULL;
	cmnd_node->rdrs = NULL;
	cmnd_node->fds[0] = -1;
	cmnd_node->fds[1] = -1;
	cmnd_node->appnd = false;
	cmnd_node->heredoc = false;
	cmnd_node->pipe = false;
	cmnd_node->next = NULL;
}

// counts how many commands within one input by '|'
int	count_cmnds(t_input *words)
{
	int		i;
	t_input	*tmp;

	i = 1;
	if (words == NULL)
		return (0);
	tmp = words;
	while (tmp != NULL)
	{
		if (tmp->type == TOKEN_PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

// counts how many tokens within one command
int	count_cmnd_len(t_input *words)
{
	int		i;
	t_input	*tmp;

	i = 0;
	if (words == NULL)
		return (0);
	tmp = words;
	while (tmp != NULL && tmp->type != TOKEN_PIPE)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

// counts how many tokens within one command skips redirs and filenames
int	count_cmnd_len_argv(t_input *words)
{
	t_input	*tmp;
	int		i;

	i = 0;
	if (words == NULL)
		return (0);
	tmp = words;
	while (tmp != NULL && tmp->type != TOKEN_PIPE)
	{
		if (!(tmp->type == TOKEN_RDR_IN || tmp->type == TOKEN_RDR_OUT
				|| tmp->type == TOKEN_APPND || tmp->type == TOKEN_HERE))
			i++;
		else
			i--;
		tmp = tmp->next;
	}
	return (i);
}

void	set_apnd_hered_pipe(t_cmnd *node)
{
	int		i;

	i = 0;
	while (node->argv_type[i])
	{
		if ((*(node->argv_type[i])) == TOKEN_APPND)
			node->appnd = true;
		else if (*(node->argv_type[i]) == TOKEN_HERE)
			node->heredoc = true;
		i++;
	}
}
