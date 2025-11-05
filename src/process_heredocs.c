/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 00:00:00 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/02 19:47:05 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	process_command_heredocs(t_cmnd *cmd, int *global_counter)
{
	t_rdrs	*rdr;
	int		result;

	rdr = cmd->rdrs;
	while (rdr)
	{
		if (rdr->redir_type == TOKEN_HERE)
		{
			result = handle_heredoc(rdr->filename, *global_counter);
			if (result == -1)
				return (-1);
			(*global_counter)++;
		}
		rdr = rdr->next;
	}
	return (0);
}

static void	cleanup_heredoc_files(int total_count)
{
	int		i;
	char	*filename;

	i = 0;
	while (i < total_count)
	{
		filename = get_heredoc_filename(i);
		if (filename)
		{
			unlink(filename);
			free(filename);
		}
		i++;
	}
}

static int	count_all_heredocs(t_cmnd *cmnd_list)
{
	t_cmnd	*current;
	int		count;

	count = 0;
	current = cmnd_list;
	while (current)
	{
		if (current->rdrs)
			count += count_heredocs_in_command(current->rdrs);
		current = current->next;
	}
	return (count);
}

void	cleanup_all_heredocs(t_cmnd *cmnd_list)
{
	int	total;

	total = count_all_heredocs(cmnd_list);
	cleanup_heredoc_files(total);
}

int	process_all_heredocs_in_pipeline(t_cmnd *cmnd_list)
{
	t_cmnd	*current;
	int		counter;

	counter = 0;
	current = cmnd_list;
	while (current)
	{
		if (current->rdrs && has_heredocs(current->rdrs))
		{
			if (process_command_heredocs(current, &counter) == -1)
			{
				cleanup_heredoc_files(counter);
				return (-1);
			}
		}
		current = current->next;
	}
	return (0);
}
