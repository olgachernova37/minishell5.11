/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_command_implementation.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:50:59 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/23 17:56:19 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset_env_var(t_env **env, char *var)
{
	t_env	*current;
	t_env	*prev;

	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, var) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (1);
}

int	find_var(char *var, t_env **env)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, var) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

int	unset_command_implementation(t_env **env, char **input)
{
	int	i;

	if (!env || !input || !input[1])
		return (0);
	i = 1;
	while (input[i])
	{
		unset_env_var(env, input[i]);
		i++;
	}
	return (0);
}
