/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command_implementation4.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:50:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/06 14:39:28 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	append_to_env(t_env *tmp, char *key, char *input)
{
	char	*new_value;
	char	*append_value;

	append_value = input_parse_value_export(input);
	new_value = ft_strjoin(tmp->value, append_value);
	if (!new_value)
	{
		free(key);
		return (1);
	}
	free(tmp->value);
	tmp->value = new_value;
	free(key);
	return (0);
}

int	var_and_value(char *input, t_env **env)
{
	t_env	*tmp;
	char	*key;
	int		is_append;

	if (!env)
		return (1);
	is_append = is_append_export(input);
	key = input_parse_key_export(input);
	if (!key)
		return (1);
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (is_append)
				return (append_to_env(tmp, key, input));
			return (update_existing_env(tmp, key, input));
		}
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return (add_new_node_ex(env, tmp, key, input));
}

t_env	*create_empty_node(char *key)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		free(key);
		return (NULL);
	}
	new_node->key = key;
	new_node->value = ft_strdup("");
	new_node->next = NULL;
	return (new_node);
}

int	update_existing_empty(t_env *tmp, char *key)
{
	free(tmp->value);
	tmp->value = ft_strdup("");
	free(key);
	return (0);
}

int	var_and_equal(char *input, t_env **env)
{
	t_env	*tmp;
	t_env	*new_node;
	char	*key;

	key = input_parse_key_export(input);
	if (!env || !(key))
		return (1);
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (update_existing_empty(tmp, key));
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	new_node = create_empty_node(key);
	if (!new_node)
		return (1);
	if (!*env)
		*env = new_node;
	else
		tmp->next = new_node;
	return (0);
}
