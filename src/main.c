/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtereshc <dtereshc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/05 23:06:14 by dtereshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			g_exit_status = 0;

static int	handle_empty_input(char *input)
{
	if (!input)
		return (1);
	normalize_input_inplace(input);
	if (*input)
		add_history(input);
	if (*input == '\0' || !validate_input(input))
	{
		free(input);
		return (1);
	}
	return (0);
}

static void	process_command_pipeline(char *input, t_env **env, char **env_array)
{
	t_cleanup	cleanup;
	t_input	*words;
	t_cmnd	*list;
	char	*extnd;

	words = NULL;
	if (!input)
		return ;
	extnd = dollar_extend(input, env);
	if (!extnd)
	{
		g_exit_status = 1;
		write(2, "minishell: dollar_extend alloc failed\n", 38);
		free(input);
		return ;
	}
	free(input);
	input = extnd;
	if (!input || !*input)
	{
		free(input);
		g_exit_status = 0;
		return ;
	}
	words = tokenize(words, input);
	if (!words)
	{
		free(input);
		g_exit_status = 0;
		return ;
	}
	list = crt_cmnd_ls(words);
	if (!list)
	{
		g_exit_status = 1;
		write(2, "minishell: crt_cmnd_ls error\n", 31);
		free(input);
		free_t_input(&words);
		return ;
	}
	if (process_all_heredocs_in_pipeline(list) == 0)
	{
		cleanup.env = env;
		cleanup.env_array = env_array;
		cleanup.cmnd_ls = &list;
		cleanup.words = &words;
		cleanup.raw_input = &input;
		what_command(&list, env, env_array, &cleanup);
	}
	cleanup_all_heredocs(list);
	free_cmnd_ls(&list, &words);
	free(input);
}

static void	initialize_shell(t_env **env, char ***env_array, char **envp)
{
	if (!envp)
	{
		write(2, "minishell: init error\n", 22);
		exit(23);
	}
	*env = env_init(envp);
	if (!*env)
	{
		write(2, "minishell: env_init failed\n", 27);
		exit(24);
	}
	read_history(".minishell_history");
	*env_array = do_env_array(*env, count_env_ls(*env));
	if (!*env_array)
	{
		write(2, "minishell: env_array alloc failed\n", 34);
		exit(25);
	}
	init_signals();
}

static char	*read_line_with_prompt(const char *prompt, int is_tty)
{
	char	*line;
	char	*result;
	size_t	len;
	ssize_t	nread;

	if (is_tty)
		return (readline(prompt));
	line = NULL;
	len = 0;
	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
		free(line);
		return (NULL);
	}
	if (nread > 0 && line[nread - 1] == '\n')
		line[nread - 1] = '\0';
	result = ft_strdup(line);
	free(line);
	return (result);
}

// и обязательно освобождать старый env_array, чтобы не текла память.
// env_array но потом обязательно обновлять, когда env меняется.
int	main(int argc, char **argv, char **envp)
{
	t_cleanup	cleanup;
	t_env	*env;
	char	*input;
	char	**env_array;
	char	*exit_argv[2];
	int		is_tty;

	(void)argc;
	(void)argv;
	is_tty = isatty(STDIN_FILENO);
	initialize_shell(&env, &env_array, envp);
	if (!is_tty)
		write(1, "minishell$ \n", 12);
	while (42)
	{
		input = read_line_with_prompt("minishell$ ", is_tty);
		signal(SIGINT, handler_sig_int);
		if (input == NULL)
		{
			exit_argv[0] = "exit";
			exit_argv[1] = NULL;
			cleanup.env = &env;
			cleanup.env_array = env_array;
			cleanup.cmnd_ls = NULL;
			cleanup.words = NULL;
			cleanup.raw_input = NULL;
			exit_command_implementation(exit_argv, &cleanup);
			break ;
		}
		if (handle_empty_input(input))
			continue ;
		process_command_pipeline(input, &env, env_array);
	}
	write_history(".minishell_history");
	free_env_array(env_array);
	free_env(&env);
	return (0);
}
