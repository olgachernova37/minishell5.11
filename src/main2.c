/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/06 14:05:20 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*expand_input(char *input, t_env **env)
{
	char	*extnd;

	extnd = dollar_extend(input, env);
	if (!extnd)
	{
		g_exit_status = 1;
		write(2, "minishell: dollar_extend alloc failed\n", 38);
		free(input);
		return (NULL);
	}
	free(input);
	return (extnd);
}

static t_input	*tokenize_input(char *input)
{
	t_input	*words;

	words = tokenize(NULL, input);
	if (!words)
	{
		free(input);
		g_exit_status = 0;
		return (NULL);
	}
	return (words);
}

static t_cmnd	*create_command_list(t_input *words, char *input)
{
	t_cmnd	*list;

	list = crt_cmnd_ls(words);
	if (!list)
	{
		g_exit_status = 1;
		write(2, "minishell: crt_cmnd_ls error\n", 31);
		free(input);
		free_t_input(&words);
		return (NULL);
	}
	return (list);
}

static void	execute_commands(t_pipeline_data *data, t_env **env,
		char **env_array)
{
	t_cleanup	cleanup;

	if (process_all_heredocs_in_pipeline(data->list) == 0)
	{
		cleanup.env = env;
		cleanup.env_array = env_array;
		cleanup.cmnd_ls = &(data->list);
		cleanup.words = &(data->words);
		cleanup.raw_input = &(data->input);
		what_command(&(data->list), env, env_array, &cleanup);
	}
	cleanup_all_heredocs(data->list);
}

void	process_command_pipeline(char *input, t_env **env, char **env_array)
{
	t_pipeline_data	data;

	if (!input)
		return ;
	data.input = expand_input(input, env);
	if (!data.input || !*data.input)
	{
		free(data.input);
		g_exit_status = 0;
		return ;
	}
	data.words = tokenize_input(data.input);
	if (!data.words)
		return ;
	data.list = create_command_list(data.words, data.input);
	if (!data.list)
		return ;
	execute_commands(&data, env, env_array);
	free_cmnd_ls(&data.list, &data.words);
	free(data.input);
}
