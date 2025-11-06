/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/06 13:52:12 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_empty_input(char *input)
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

void	initialize_shell(t_env **env, char ***env_array, char **envp)
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

char	*read_line_with_prompt(const char *prompt, int is_tty)
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
