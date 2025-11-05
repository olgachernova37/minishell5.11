/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implem_redir3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 00:00:00 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/02 21:27:43 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_non_heredoc_redir(t_rdrs *rdr, int *heredoc_fd)
{
	if (process_single_redir(rdr) != 0)
	{
		if (*heredoc_fd != -1)
			close(*heredoc_fd);
		return (1);
	}
	return (0);
}

int	setup_heredoc_input(int *heredoc_fd)
{
	if (*heredoc_fd != -1)
	{
		if (dup2(*heredoc_fd, STDIN_FILENO) == -1)
		{
			close(*heredoc_fd);
			return (1);
		}
		close(*heredoc_fd);
		*heredoc_fd = -1;
	}
	return (0);
}

int	process_redirections_loop(t_rdrs *rdr_list, int *heredoc_fd)
{
	t_rdrs	*rdr;

	rdr = rdr_list;
	while (rdr)
	{
		if (rdr->redir_type != TOKEN_HERE)
		{
			if (handle_non_heredoc_redir(rdr, heredoc_fd) != 0)
				return (1);
		}
		else
		{
			if (setup_heredoc_input(heredoc_fd) != 0)
				return (1);
		}
		rdr = rdr->next;
	}
	return (0);
}

int	implamentation_redir(t_cmnd *cmnd)
{
	int	heredoc_fd;

	heredoc_fd = process_heredocs_for_command(cmnd->rdrs);
	if (heredoc_fd == -1 && has_heredocs(cmnd->rdrs))
		return (1);
	if (process_redirections_loop(cmnd->rdrs, &heredoc_fd) != 0)
		return (1);
	if (heredoc_fd != -1)
	{
		if (dup2(heredoc_fd, STDIN_FILENO) == -1)
		{
			close(heredoc_fd);
			return (1);
		}
		close(heredoc_fd);
	}
	return (0);
}
