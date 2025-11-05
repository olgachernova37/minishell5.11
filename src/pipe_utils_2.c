/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 21:55:22 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/02 22:00:10 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static pid_t	get_shell_pid(void)
{
	static pid_t	shell_pid = 0;

	if (shell_pid == 0)
		shell_pid = getpid();
	return (shell_pid);
}

static char	*build_heredoc_filename(char *pid_str, char *counter_str)
{
	char	*base_filename;
	char	*filename;

	base_filename = create_base_filename(pid_str);
	if (!base_filename)
		return (NULL);
	filename = ft_strjoin(base_filename, counter_str);
	free(base_filename);
	return (filename);
}

char	*get_heredoc_filename(int counter)
{
	char	*pid_str;
	char	*counter_str;
	char	*filename;

	pid_str = ft_itoa(get_shell_pid());
	counter_str = ft_itoa(counter);
	if (!pid_str || !counter_str)
	{
		free(pid_str);
		free(counter_str);
		return (NULL);
	}
	filename = build_heredoc_filename(pid_str, counter_str);
	free(pid_str);
	free(counter_str);
	return (filename);
}
