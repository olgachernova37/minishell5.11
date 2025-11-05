/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtereshc <dtereshc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:50:50 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/02 14:20:57 by dtereshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

// func for tests
void	print_my_env(t_env *env)
{
	t_env	*tmp;

	if (env == NULL)
		return ;
	tmp = env;
	while (tmp != NULL)
	{
		printf("%s=%s", tmp->key, tmp->value);
		printf("\n");
		tmp = tmp->next;
	}
}

void	add_new_node(t_env **list, t_env *new_node)
{
	t_env	*tmp;

	if (!list || !new_node)
		return ;
	if (*list == NULL)
		*list = new_node;
	else
	{
		tmp = *list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

// Creates a single environment node from an environment variable string
t_env	*create_env_node_env_init(char *env_str)
{
	t_env	*new_node;
	char	*equals_pos;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		exit(1);
	new_node->next = NULL;
	equals_pos = ft_strchr(env_str, '=');
	if (equals_pos)
	{
		*equals_pos = '\0';
		new_node->key = strdup(env_str);
		*equals_pos = '=';
		new_node->value = strdup(equals_pos + 1);
	}
	else
	{
		new_node->key = strdup(env_str);
		new_node->value = strdup("");
	}
	return (new_node);
}

// Initializes the environment list from envp array
t_env	*env_init(char **envp)
{
	t_env	*new_node;
	t_env	*envp_list;
	int		i;

	i = 0;
	envp_list = NULL;
	while (envp[i])
	{
		new_node = create_env_node_env_init(envp[i]);
		add_new_node(&envp_list, new_node);
		i++;
	}
	return (envp_list);
}
