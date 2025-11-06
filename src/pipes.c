/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:51:30 by dtereshc          #+#    #+#             */
/*   Updated: 2025/11/06 13:37:51 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	finish_child(t_cmnd **cmnd, int pipes_qntt, pid_t *pids, int i)
{
	int	l_st;

	close_ends(cmnd);
	l_st = find_last_state(pids, i, pipes_qntt);
	free(pids);
	if (WIFEXITED(l_st))
		return (WEXITSTATUS(l_st));
	if (WIFSIGNALED(l_st))
		return (128 + WTERMSIG(l_st));
	return (1);
}

void	free_current_cmnd(t_cmnd *cur_cmnd)
{
	if (!cur_cmnd)
		return ;
	if (cur_cmnd->argv)
		free(cur_cmnd->argv);
	if (cur_cmnd->full_argv)
		free(cur_cmnd->full_argv);
	if (cur_cmnd->argv_type)
		free(cur_cmnd->argv_type);
	if (cur_cmnd->rdrs)
		free_rdrs(cur_cmnd->rdrs);
	free(cur_cmnd);
}

int	creat_child(int pipes_qntt, t_cmnd **cmnd, t_cleanup *cleanup)
{
	int		i;
	pid_t	*pids;
	t_cmnd	*cur_cmnd;

	i = 0;
	if (!cmnd || !*cmnd)
		return (1);
	cur_cmnd = *cmnd;
	pids = malloc(sizeof(pid_t) * (pipes_qntt + 1));
	if (!pids)
		exit(EXIT_FAILURE);
	while (cur_cmnd)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			return (pid_err(pids, i));
		if (pids[i] == 0)
		{
			free(pids);
			child_logic(cmnd, cur_cmnd, cleanup);
		}
		cur_cmnd = cur_cmnd->next;
		i++;
	}
	return (finish_child(cmnd, pipes_qntt, pids, i));
}

int	do_pipeline(t_cmnd **cmnd, t_cleanup *cleanup)
{
	int	pipes_qntt;
	int	(*fds)[2];

	pipes_qntt = 0;
	if (!cmnd || !*cmnd)
		return (0);
	fds = allocate_fds(cmnd, &pipes_qntt);
	if (pipes_qntt == 0)
		return (0);
	if (!fds)
		return (1);
	connect_fds(cmnd, pipes_qntt, fds);
	free(fds);
	g_exit_status = creat_child(pipes_qntt, cmnd, cleanup);
	return (g_exit_status);
}
