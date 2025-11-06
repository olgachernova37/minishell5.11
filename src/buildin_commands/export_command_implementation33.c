/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command_implementation33.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:50:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/06 14:40:39 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	export_command_implementation(char **input, t_env **env)
{
	int	i;

	i = 1;
	if (input[i] == NULL)
	{
		return (only_export(*env));
	}
	else if ((input[i] != NULL))
	{
		return (parsing_export(input, env));
	}
	return (0);
}
