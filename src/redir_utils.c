/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 21:01:21 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/02 19:47:05 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_filename(char *filename)
{
	free(filename);
}

void	print_heredoc_eof_warning(char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document delimited by ", 2);
	ft_putstr_fd("end-of-file (wanted `", 2);
	if (delimiter)
		ft_putstr_fd(delimiter, 2);
	else
		ft_putstr_fd("(null)", 2);
	ft_putstr_fd("')\n", 2);
}

int	handle_heredoc_exit_conditions(char *line, char *delimiter)
{
	if (!line)
	{
		if (g_exit_status == 130)
			return (1);
		print_heredoc_eof_warning(delimiter);
		return (1);
	}
	return (0);
}

int	check_delimiter_match(char *line, char *delimiter, size_t delim_len)
{
	if (ft_strncmp(line, delimiter, delim_len) == 0
		&& ft_strlen(line) == delim_len)
	{
		free(line);
		return (1);
	}
	return (0);
}
