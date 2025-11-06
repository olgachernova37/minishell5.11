/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:51:30 by dtereshc          #+#    #+#             */
/*   Updated: 2025/11/06 13:33:49 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cleanup_and_exit(t_cmnd **cmnd, t_cleanup *cleanup, int exit_code)
{
	free_child_structures(cmnd, cleanup, NULL);
	free_env_array(cleanup->env_array);
	free_env(cleanup->env);
	exit(exit_code);
}

static void	init_builtin_cleanup(t_cleanup *builtin_cleanup, t_cleanup *cleanup)
{
	builtin_cleanup->env = cleanup->env;
	builtin_cleanup->env_array = cleanup->env_array;
	builtin_cleanup->cmnd_ls = NULL;
	builtin_cleanup->words = NULL;
	builtin_cleanup->raw_input = NULL;
}

static void	handle_builtin_command(t_cmnd **cmnd, t_cmnd *cur_cmnd,
		t_cleanup *cleanup)
{
	int			exit_code;
	t_cleanup	builtin_cleanup;

	init_builtin_cleanup(&builtin_cleanup, cleanup);
	exit_code = which_buildin_command(cur_cmnd, cleanup->env,
			cleanup->env_array, &builtin_cleanup);
	cleanup_and_exit(cmnd, cleanup, exit_code);
}

static void	handle_external_command(t_cmnd **cmnd, t_cmnd *cur_cmnd,
		t_cleanup *cleanup)
{
	int	exit_code;

	exit_code = execve_child(cur_cmnd, cleanup->env, cleanup->env_array);
	cleanup_and_exit(cmnd, cleanup, exit_code);
}

void	child_logic(t_cmnd **cmnd, t_cmnd *cur_cmnd, t_cleanup *cleanup)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	connect_ends(cur_cmnd);
	close_ends(cmnd);
	if (implamentation_redir(cur_cmnd))
		cleanup_and_exit(cmnd, cleanup, 1);
	if (!cur_cmnd->argv || !cur_cmnd->argv[0])
		cleanup_and_exit(cmnd, cleanup, 0);
	if (is_command_buildin(cur_cmnd->argv))
		handle_builtin_command(cmnd, cur_cmnd, cleanup);
	else
		handle_external_command(cmnd, cur_cmnd, cleanup);
}
