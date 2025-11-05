/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:45:07 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/05 21:16:05 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmnd	*skip_cmnds(t_cmnd *cmnd)
{
	if (!cmnd)
		return (NULL);
	while (cmnd && cmnd->pipe)
		cmnd = cmnd->next;
	if (cmnd)
		cmnd = cmnd->next;
	return (cmnd);
}

t_cmnd	*what_cmnd_shrt_0(t_cmnd *cmnd, int stdin_backup, int stdout_backup)
{
	if (!cmnd)
		return (NULL);
	cmnd = cmnd->next;
	g_exit_status = 1;
	secure_fd(stdin_backup, stdout_backup);
	return (cmnd);
}

void	what_cmnd_shrt_1(t_cmnd *cmnd, t_env **my_env, char **env_array,
		t_cleanup *cleanup)
{
	if (!cmnd->argv || !cmnd->argv[0] || !cmnd->argv[0][0])
	{
		if (cmnd->argv && cmnd->argv[0] && !cmnd->argv[0][0])
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(cmnd->argv[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			g_exit_status = 127;
		}
		else
			g_exit_status = 0;
		return ;
	}
	if (is_command_buildin(cmnd->argv))
		g_exit_status = which_buildin_command(cmnd, my_env, env_array,
				cleanup);
	else
		g_exit_status = other_commands_implementation(cmnd->argv, my_env);
}

void	what_command(t_cmnd **cmnd_ls, t_env **my_env, char **array_env,
		t_cleanup *cleanup)
{
	t_cmnd	*cmnd;
	int		stdin_backup;
	int		stdout_backup;

	cmnd = *cmnd_ls;
	while (cmnd != NULL)
	{
		stdin_backup = dup(STDIN_FILENO);
		stdout_backup = dup(STDOUT_FILENO);
		if (cmnd->next)
		{
			g_exit_status = do_pipeline(cmnd_ls, cleanup);
			cmnd = skip_cmnds(cmnd);
			continue ;
		}
		else if (implamentation_redir(cmnd))
		{
			cmnd = what_cmnd_shrt_0(cmnd, stdin_backup, stdout_backup);
			continue ;
		}
		what_cmnd_shrt_1(cmnd, my_env, array_env, cleanup);
		secure_fd(stdin_backup, stdout_backup);
		cmnd = cmnd->next;
	}
}
