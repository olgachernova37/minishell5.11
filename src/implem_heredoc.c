/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implem_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 00:00:00 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/05 23:35:32 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*create_base_filename(char *pid_str)
{
	char	*temp;
	char	*base_filename;

	temp = ft_strjoin("/tmp/.heredoc_", pid_str);
	if (!temp)
		return (NULL);
	base_filename = ft_strjoin(temp, "_");
	free(temp);
	return (base_filename);
}

void	heredoc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		rl_replace_line("", 0);
		rl_done = 1;
		write(1, "\n", 1);
		rl_on_new_line();
	}
}

int	write_heredoc_content(int fd, char *delimiter)
{
	char	*line;
	size_t	delim_len;

	delim_len = ft_strlen(delimiter);
	signal(SIGINT, heredoc_signal_handler);
	while (1)
	{
		line = readline("> ");
		if (g_exit_status == 130)
		{
			free(line);
			break ;
		}
		if (handle_heredoc_exit_conditions(line, delimiter))
			break ;
		if (check_delimiter_match(line, delimiter, delim_len))
			break ;
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	signal(SIGINT, handler_sig_int);
	return (0);
}

int	handle_heredoc(char *delimiter, int counter)
{
	char	*filename;
	int		fd;

	filename = get_heredoc_filename(counter);
	if (!filename)
		return (-1);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
	{
		perror(filename);
		free(filename);
		return (-1);
	}
	write_heredoc_content(fd, delimiter);
	close(fd);
	free(filename);
	if (g_exit_status == 130)
		return (-1);
	return (0);
}
