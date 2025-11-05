/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command_implementation.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:50:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/23 16:42:17 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_array_size(char **array)
{
	int	size;

	size = 0;
	while (array[size])
		size++;
	return (size);
}

char	**bubble_sort(char **array, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(array[j], array[j + 1]) > 0)
			{
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (array);
}

int	print_and_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("declare -x %s\n", array[i]);
		free(array[i]);
		i++;
	}
	free(array);
	return (0);
}

char	*get_env_string(t_env *tmp)
{
	if (tmp->key && tmp->value && ft_strlen(tmp->value) > 0)
		return (strjoin_modified(tmp->key, tmp->value));
	else if (tmp->key)
		return (ft_strdup(tmp->key));
	return (ft_strdup(""));
}

char	**fill_export_array(t_env *env, int size)
{
	char	**array;
	int		i;
	t_env	*tmp;

	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp != NULL)
	{
		array[i] = get_env_string(tmp);
		if (!array[i])
		{
			while (--i >= 0)
				free(array[i]);
			free(array);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
