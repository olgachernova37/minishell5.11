/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/06 14:08:22 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			g_exit_status = 0;

static int	handle_eof(t_env **env, char **env_array)
{
	t_cleanup	cleanup;
	char		*exit_argv[2];

	exit_argv[0] = "exit";
	exit_argv[1] = NULL;
	setup_exit_cleanup(&cleanup, env, env_array);
	exit_command_implementation(exit_argv, &cleanup);
	return (1);
}

static void	process_input_line(char *input, t_env **env, char **env_array)
{
	if (handle_empty_input(input))
		return ;
	process_command_pipeline(input, env, env_array);
}

static void	main_loop(t_env **env, char **env_array, int is_tty)
{
	char	*input;

	while (42)
	{
		input = read_line_with_prompt("minishell$ ", is_tty);
		signal(SIGINT, handler_sig_int);
		if (input == NULL)
		{
			if (handle_eof(env, env_array))
				break ;
		}
		process_input_line(input, env, env_array);
	}
}

static void	cleanup_and_exit2(t_env **env, char **env_array)
{
	write_history(".minishell_history");
	free_env_array(env_array);
	free_env(env);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	char	**env_array;
	int		is_tty;

	(void)argc;
	(void)argv;
	is_tty = isatty(STDIN_FILENO);
	initialize_shell(&env, &env_array, envp);
	if (!is_tty)
		write(1, "minishell$ \n", 12);
	main_loop(&env, env_array, is_tty);
	cleanup_and_exit2(&env, env_array);
	return (0);
}
