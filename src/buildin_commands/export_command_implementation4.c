/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command_implementation4.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:50:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/01 20:21:57 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	var_and_value(char *input, t_env **env)
{
	t_env	*tmp;
	char	*key;

	if (!env)
		return (1);
	key = input_parse_key_export(input);
	if (!key)
		return (1);
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (update_existing_env(tmp, key, input));
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

int	one_var(char *input, t_env **env)
{
	int	form;

	form = check_export_form(input);
	if (form == 0)
	{
		return (only_var(input, env));
	}
	else if (form == 1)
	{
		return (var_and_equal(input, env));
	}
	else if (form == 2)
	{
		return (var_and_value(input, env));
	}
	return (0);
}
