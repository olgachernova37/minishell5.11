/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_command_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 15:10:44 by dtereshc          #+#    #+#             */
/*   Updated: 2025/11/06 13:11:20 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	match_buildin(char *og_input, char *match_cmnd)
{
	while (*og_input == *match_cmnd && *match_cmnd)
	{
		og_input++;
		match_cmnd++;
	}
	if (!(*match_cmnd) && !(*og_input))
		return (1);
	return (0);
}

bool	is_command_buildin(char **input)
{
	if (!input || !input[0])
		return (false);
	if (match_buildin(input[0], "cd"))
		return (true);
	else if (match_buildin(input[0], "pwd"))
		return (true);
	else if (match_buildin(input[0], "export"))
		return (true);
	else if (match_buildin(input[0], "unset"))
		return (true);
	else if (match_buildin(input[0], "echo"))
		return (true);
	else if (match_buildin(input[0], "env"))
		return (true);
	else if (match_buildin(input[0], "exit"))
		return (true);
	else
		return (false);
}

int	which_buildin_command(t_cmnd *cmnd, t_env **my_env, char **env_array,
		t_cleanup *cleanup)
{
	if (match_buildin(cmnd->argv[0], "echo"))
		return (echo_command_implementation(&cmnd));
	else if (match_buildin(cmnd->argv[0], "pwd"))
		return (pwd_command_implementation());
	else if (match_buildin(cmnd->argv[0], "export"))
		return (export_command_implementation(cmnd->argv, my_env));
	else if (match_buildin(cmnd->argv[0], "unset"))
		return (unset_command_implementation(my_env, cmnd->argv));
	else if (match_buildin(cmnd->argv[0], "cd"))
		return (cd_command_implementation(cmnd->argv, *my_env));
	else if (match_buildin(cmnd->argv[0], "exit"))
		return (exit_command_implementation(cmnd->argv, cleanup));
	else if (match_buildin(cmnd->argv[0], "env"))
	{
		if (cmnd->argv[1] != NULL)
		{
			ft_putstr_fd("bash: env: ", 2);
			ft_putstr_fd(cmnd->argv[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (127);
		}
		print_my_env(*my_env);
		return (0);
	}
	return (0);
}

void	secure_fd(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}
