/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtereshc <dtereshc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:26:32 by dtereshc          #+#    #+#             */
/*   Updated: 2025/11/02 14:21:58 by dtereshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_pipeline(t_cmnd **cmnd)
{
	int		i;
	t_cmnd	*p;

	i = 0;
	p = *cmnd;
	while (p)
	{
		if (p->pipe)
			i++;
		p = p->next;
	}
	return (i);
}

int	close_fds(int pipes_qntt, int (*fds)[2])
{
	int	i;

	i = 0;
	if (!fds)
		return (1);
	while (i < pipes_qntt)
	{
		close(fds[i][0]);
		close(fds[i][1]);
		i++;
	}
	free(fds);
	return (1);
}

// closes all pipe ends and sets them to -1
void	close_ends(t_cmnd **cmnd)
{
	t_cmnd	*cur_cmnd;

	if (!cmnd || !*cmnd)
		return ;
	cur_cmnd = *cmnd;
	while (cur_cmnd)
	{
		if (cur_cmnd->fds[0] != -1)
		{
			close(cur_cmnd->fds[0]);
			cur_cmnd->fds[0] = -1;
		}
		if (cur_cmnd->fds[1] != -1)
		{
			close(cur_cmnd->fds[1]);
			cur_cmnd->fds[1] = -1;
		}
		cur_cmnd = cur_cmnd->next;
	}
}

void	connect_ends(t_cmnd *cmnd)
{
	if (!cmnd)
		return ;
	if (cmnd->fds[0] != -1 && dup2(cmnd->fds[0], STDIN_FILENO) == -1)
	{
		perror("dup2 in");
		exit(1);
	}
	if (cmnd->fds[1] != -1 && dup2(cmnd->fds[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 out");
		exit(1);
	}
}

int	pid_err(pid_t *pids, int i)
{
	int	j;

	j = 0;
	perror("fork");
	while (j < i)
		waitpid(pids[j++], NULL, 0);
	free(pids);
	return (1);
}
