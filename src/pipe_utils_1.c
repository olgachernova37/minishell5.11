/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:29:26 by dtereshc          #+#    #+#             */
/*   Updated: 2025/11/06 12:57:46 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int (*allocate_fds(t_cmnd **cmnd, int *pipes_qntt))[2]
{
	int	(*fds)[2];
	int	pipes;

	if (!cmnd || !*cmnd)
	{
		if (pipes_qntt)
			*pipes_qntt = 0;
		return (NULL);
	}
	pipes = is_pipeline(cmnd);
	if (pipes_qntt)
		*pipes_qntt = pipes;
	if (pipes <= 0)
		return (NULL);
	fds = malloc(sizeof(int [2]) * pipes);
	if (!fds)
		return (NULL);
	piping(pipes, fds);
	return (fds);
}


void	piping(int pipes, int (*fds)[2])
{
	int	i;

	i = 0;
	while (i < pipes)
	{
		if (pipe(fds[i]) == -1)
		{
			perror("pipe");
			close_fds(i, fds);
			exit(12);
		}
		i++;
	}
}

void	connect_fds(t_cmnd **cmnd, int pipes_qntt, int (*fds)[2])
{
	t_cmnd	*cur_cmnd;
	int		i;

	i = 0;
	cur_cmnd = *cmnd;
	if (!cmnd || !*cmnd || !fds)
		return ;
	while (i < pipes_qntt + 1 && cur_cmnd)
	{
		if (pipes_qntt > 0)
		{
			if (!i)
				cur_cmnd->fds[1] = fds[i][1];
			else if (i == pipes_qntt)
				cur_cmnd->fds[0] = fds[pipes_qntt - 1][0];
			else
			{
				cur_cmnd->fds[0] = fds[i - 1][0];
				cur_cmnd->fds[1] = fds[i][1];
			}
		}
		cur_cmnd = cur_cmnd->next;
		i++;
	}
}

int	execve_child(t_cmnd *cmnd, t_env **my_env, char **array_env)
{
	char	*path;

	path = find_command_path(cmnd->argv, my_env);
	if (path)
	{
		execve(path, cmnd->argv, array_env);
		perror("execve");
		free(path);
		return (127);
	}
	else
	{
		printf("bash: %s: command not found\n", cmnd->argv[0]);
		return (127);
	}
}

int	find_last_state(pid_t *pids, int i, int pipes_qntt)
{
	int	l_st;
	int	st;
	int	k;

	k = 0;
	l_st = 0;
	while (k < i)
	{
		waitpid(pids[k], &st, 0);
		if (k == pipes_qntt)
			l_st = st;
		k++;
	}
	return (l_st);
}
