/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_commands2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/05 16:26:12 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_direct_path_command(char **input, t_env **env) // new
{
	int			i;
	struct stat	st;

	if (stat(input[0], &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(input[0], 2);
			ft_putstr_fd(": Is a directory\n", 2);
			return (126);
		}
		if (access(input[0], X_OK) == 0)
		{
			i = execute_command(input[0], input, env); //new
			return (i);
		}
		else
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(input[0], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			return (126);
		}
	}
	else
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(input[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (127);
	}
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

int	other_commands_implementation(char **input, t_env **env)
{
	if (!input || !input[0])
		return (0);
	if (ft_strchr(input[0], '/'))
		return (handle_direct_path_command(input, env));
	else
		return (handle_path_command(input, env));
}
