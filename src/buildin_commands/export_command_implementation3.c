/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command_implementation3.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:50:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/06 14:36:10 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*input_parse_key_export(char *input)
{
	char	*eq;
	char	*plus;

	plus = ft_strchr(input, '+');
	eq = ft_strchr(input, '=');
	if (plus && plus + 1 == eq)
		return (ft_substr(input, 0, plus - input));
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

int	is_append_export(char *input)
{
	char	*plus;
	char	*eq;

	plus = ft_strchr(input, '+');
	eq = ft_strchr(input, '=');
	if (plus && eq && plus + 1 == eq)
		return (1);
	return (0);
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
