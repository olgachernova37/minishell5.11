/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command_implementation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:50:50 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/06 15:08:48 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ft_fprintf("exit: %s: numeric argument required\n", arg);
// Note: This function doesn't free memory because it's called from
// parse_and_validate_exit_arg which is called from exit_command_implementation
// The parent function will handle cleanup if needed
void	exit_with_numeric_error(char *arg, t_cleanup *cleanup)
{
	write(2, "exit:  ", 7);
	write(2, arg, ft_strlen(arg));
	write(2, " : numeric argument required\n", 29);
	g_exit_status = 2;
	write_history(".minishell_history");
	rl_clear_history();
	if (cleanup->raw_input && *cleanup->raw_input)
		free(*cleanup->raw_input);
	if (cleanup->cmnd_ls && cleanup->words)
		free_cmnd_ls(cleanup->cmnd_ls, cleanup->words);
	free_env_array(cleanup->env_array);
	free_env(cleanup->env);
	exit(g_exit_status);
}

long long	parse_and_validate_exit_arg(char *arg, t_cleanup *cleanup)
{
	int	i;

	i = 0;
	if (arg[0] == '-' || arg[0] == '+')
		i++;
	if (arg[i] == '\0')
		exit_with_numeric_error(arg, cleanup);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			exit_with_numeric_error(arg, cleanup);
		i++;
	}
	return ((long long)ft_atoi(arg));
}

int	exit_command_implementation(char **input, t_cleanup *cleanup)
{
	long long	val;

	if (isatty(STDIN_FILENO))
		write(2, "exit\n", 5);
	if (input[1])
	{
		val = parse_and_validate_exit_arg(input[1], cleanup);
		if (input[2])
		{
			ft_fprintf(STDERR_FD, "exit: too many arguments\n");
			g_exit_status = 1;
			return (1);
		}
		g_exit_status = (unsigned char)val;
	}
	write_history(".minishell_history");
	rl_clear_history();
	if (cleanup->raw_input && *cleanup->raw_input)
		free(*cleanup->raw_input);
	if (cleanup->cmnd_ls && cleanup->words)
		free_cmnd_ls(cleanup->cmnd_ls, cleanup->words);
	free_env_array(cleanup->env_array);
	free_env(cleanup->env);
	exit(g_exit_status);
}
