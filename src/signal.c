/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:07:30 by dtereshc          #+#    #+#             */
/*   Updated: 2025/11/04 23:22:53 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler_sig_int(int sig)
{
	if (sig == SIGINT)
	{
		// rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		g_exit_status = 130;
		rl_redisplay();
	}
}

void	handler_sig_quit(int sig)
{
	if (sig == SIGQUIT)
	{
		g_exit_status = 131;
		rl_on_new_line();
		rl_redisplay();
	}
}

int	exit_func(void)
{
	return (EXIT_SUCCESS);
}

void	init_signals(void)
{
	// rl_event_hook = exit_func;
	signal(SIGINT, handler_sig_int);
	signal(SIGQUIT, handler_sig_quit);
}
