/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implem_redir2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtereshc <dtereshc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 00:00:00 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/03 20:16:35 by dtereshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	process_one_heredoc(int counter, int *last_heredoc_fd)
{
	int		fd;
	char	*filename;

	if (*last_heredoc_fd != -1)
		close(*last_heredoc_fd);
	filename = get_heredoc_filename(counter);
	if (!filename)
		return (-1);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
	{
		if (*last_heredoc_fd != -1)
			close(*last_heredoc_fd);
		return (-1);
	}
	*last_heredoc_fd = fd;
	return (0);
}

int	count_heredocs_in_command(t_rdrs *rdr_list)
{
	t_rdrs	*current;
	int		count;

	count = 0;
	current = rdr_list;
	while (current)
	{
		if (current->redir_type == TOKEN_HERE)
			count++;
		current = current->next;
	}
	return (count);
}

int	process_heredocs_for_command(t_rdrs *rdr_list)
{
	t_rdrs	*current;
	int		counter;
	int		last_heredoc_fd;

	counter = 0;
	last_heredoc_fd = -1;
	current = rdr_list;
	while (current)
	{
		if (current->redir_type == TOKEN_HERE)
		{
			if (process_one_heredoc(counter, &last_heredoc_fd) == -1)
				return (-1);
			counter++;
		}
		current = current->next;
	}
	return (last_heredoc_fd);
}

int	has_heredocs(t_rdrs *rdr_list)
{
	t_rdrs	*current;

	current = rdr_list;
	while (current)
	{
		if (current->redir_type == TOKEN_HERE)
			return (1);
		current = current->next;
	}
	return (0);
}
