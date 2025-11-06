/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:51:30 by dtereshc          #+#    #+#             */
/*   Updated: 2025/11/06 12:57:42 by olcherno         ###   ########.fr       */
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

static void	free_child_structures(t_cmnd **cmnd, t_cleanup *cleanup,
		t_cmnd *keep)
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
		{
			if (tmp->argv)
				free(tmp->argv);
			if (tmp->full_argv)
				free(tmp->full_argv);
			if (tmp->argv_type)
				free(tmp->argv_type);
			if (tmp->rdrs)
				free_rdrs(tmp->rdrs);
			free(tmp);
		}
		tmp = next;
	}
	if (cleanup->words && *cleanup->words)
		free_t_input(cleanup->words);
	if (cleanup->raw_input && *cleanup->raw_input)
		free(*cleanup->raw_input);
}

static void	free_current_cmnd(t_cmnd *cur_cmnd)
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

void	child_logic(t_cmnd **cmnd, t_cmnd *cur_cmnd, t_cleanup *cleanup)
{
	int			exit_code;
	t_cleanup	builtin_cleanup;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	connect_ends(cur_cmnd);
	close_ends(cmnd);
	if (implamentation_redir(cur_cmnd))
	{
		free_child_structures(cmnd, cleanup, NULL);
		free_env_array(cleanup->env_array);
		free_env(cleanup->env);
		exit(1);
	}
	if (!cur_cmnd->argv || !cur_cmnd->argv[0])
	{
		free_child_structures(cmnd, cleanup, NULL);
		free_env_array(cleanup->env_array);
		free_env(cleanup->env);
		exit(0);
	}
	if (is_command_buildin(cur_cmnd->argv))
	{
		builtin_cleanup.env = cleanup->env;
		builtin_cleanup.env_array = cleanup->env_array;
		builtin_cleanup.cmnd_ls = NULL;
		builtin_cleanup.words = NULL;
		builtin_cleanup.raw_input = NULL;
		exit_code = which_buildin_command(cur_cmnd, cleanup->env,
				cleanup->env_array, &builtin_cleanup);
		free_child_structures(cmnd, cleanup, NULL);
		free_env_array(cleanup->env_array);
		free_env(cleanup->env);
		exit(exit_code);
	}
	else
	{
		exit_code = execve_child(cur_cmnd, cleanup->env, cleanup->env_array);
		free_child_structures(cmnd, cleanup, NULL);
		free_env_array(cleanup->env_array);
		free_env(cleanup->env);
		exit(exit_code);
	}
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

// returns exit_status of the last command in pipeline
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
