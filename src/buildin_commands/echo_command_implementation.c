/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command_implementation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:26:59 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/06 13:09:51 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo_command_implementation(t_cmnd **cmnd_ls)
{
	int	i;
	int	y;
	int	n_flag;

	n_flag = 0;
	i = 1;
	y = 1;
	if ((*cmnd_ls)->argv[i] && ft_strncmp((*cmnd_ls)->argv[1], "-n", 3) == 0)
	{
		n_flag = 1;
		y = 2;
	}
	while ((*cmnd_ls)->argv[y] != NULL)
	{
		write(STDOUT_FILENO, (*cmnd_ls)->argv[y],
			ft_strlen((*cmnd_ls)->argv[y]));
		if ((*cmnd_ls)->argv[y + 1])
			write(STDOUT_FILENO, " ", 1);
		y++;
	}
	if (n_flag == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
