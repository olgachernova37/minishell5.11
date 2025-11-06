/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_commands2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/06 13:17:58 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_command_error(char *cmd, char *msg, int error_code)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (error_code)
		ft_putstr_fd(strerror(errno), 2);
	else
		ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

static int	handle_file_stat_error(char *cmd)
{
	print_command_error(cmd, NULL, 1);
	return (127);
}

static int	execute_if_accessible(char *path, char **input, t_env **env)
{
	int	exit_code;

	if (access(path, X_OK) == 0)
	{
		exit_code = execute_command(path, input, env);
		return (exit_code);
	}
	else
	{
		print_command_error(input[0], NULL, 1);
		return (126);
	}
}

int	handle_direct_path_command(char **input, t_env **env)
{
	struct stat	st;

	if (stat(input[0], &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			print_command_error(input[0], "Is a directory", 0);
			return (126);
		}
		return (execute_if_accessible(input[0], input, env));
	}
	else
		return (handle_file_stat_error(input[0]));
}

int	handle_path_command(char **input, t_env **env)
{
	char	*path_with_command;
	int		i;

	path_with_command = find_command_path(input, env);
	if (path_with_command)
	{
		i = execute_command(path_with_command, input, env);
		free(path_with_command);
		return (i);
	}
	else
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(input[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
}
