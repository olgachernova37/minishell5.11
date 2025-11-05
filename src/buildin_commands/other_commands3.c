/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_commands3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtereshc <dtereshc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 00:00:00 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/02 14:24:31 by dtereshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*get_path_from_env(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "PATH", 4) == 0 && ft_strlen(tmp->key) == 4)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*try_path(char *dir, char *command)
{
	char	*path_with_command;
	char	*tmp;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	path_with_command = ft_strjoin(tmp, command);
	free(tmp);
	if (!path_with_command)
		return (NULL);
	if (access(path_with_command, X_OK) == 0)
		return (path_with_command);
	free(path_with_command);
	return (NULL);
}

char	*find_command_path(char **input, t_env **env)
{
	char	**splited_path;
	char	*path_value;
	char	*result;
	int		i;

	path_value = get_path_from_env(env);
	if (!path_value)
		return (NULL);
	splited_path = ft_split(path_value, ':');
	if (!splited_path)
		return (NULL);
	i = 0;
	while (splited_path[i])
	{
		result = try_path(splited_path[i], input[0]);
		if (result)
		{
			free_split(splited_path);
			return (result);
		}
		i++;
	}
	free_split(splited_path);
	return (NULL);
}
