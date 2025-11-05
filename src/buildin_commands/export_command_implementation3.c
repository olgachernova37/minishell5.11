/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command_implementation.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:50:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/07 23:38:50 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*input_parse_key_export(char *input)
{
	char	*eq;

	eq = ft_strchr(input, '=');
	if (!eq)
		return (ft_strdup(input));
	return (ft_substr(input, 0, eq - input));
}

char	*input_parse_value_export(char *input)
{
	char	*eq;

	eq = ft_strchr(input, '=');
	if (!eq)
		return (NULL);
	return (eq + 1);
}

t_env	*create_env_node(char *key, char *input)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		free(key);
		return (NULL);
	}
	new_node->key = key;
	new_node->value = ft_strdup(input_parse_value_export(input));
	new_node->next = NULL;
	return (new_node);
}

int	update_existing_env(t_env *tmp, char *key, char *input)
{
	free(tmp->value);
	tmp->value = ft_strdup(input_parse_value_export(input));
	free(key);
	return (0);
}

int	add_new_node_ex(t_env **env, t_env *tmp, char *key, char *input)
{
	t_env	*new_node;

	new_node = create_env_node(key, input);
	if (!new_node)
		return (1);
	if (!*env)
		*env = new_node;
	else
		tmp->next = new_node;
	return (0);
}
