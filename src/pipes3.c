/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:51:30 by dtereshc          #+#    #+#             */
/*   Updated: 2025/11/06 13:36:48 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_single_cmnd(t_cmnd *cmnd)
{
	if (cmnd->argv)
		free(cmnd->argv);
	if (cmnd->full_argv)
		free(cmnd->full_argv);
	if (cmnd->argv_type)
		free(cmnd->argv_type);
	if (cmnd->rdrs)
		free_rdrs(cmnd->rdrs);
	free(cmnd);
}

static void	free_cmnd_list(t_cmnd **cmnd, t_cmnd *keep)
{
	t_cmnd	*tmp;
	t_cmnd	*next;

	if (!cmnd || !*cmnd)
		return ;
	tmp = *cmnd;
	while (tmp)
	{
		next = tmp->next;
		if (tmp != keep)
			free_single_cmnd(tmp);
		tmp = next;
	}
}

static void	free_cleanup_data(t_cleanup *cleanup)
{
	if (cleanup->words && *cleanup->words)
		free_t_input(cleanup->words);
	if (cleanup->raw_input && *cleanup->raw_input)
		free(*cleanup->raw_input);
}

void	free_child_structures(t_cmnd **cmnd, t_cleanup *cleanup, t_cmnd *keep)
{
	free_cmnd_list(cmnd, keep);
	free_cleanup_data(cleanup);
}
