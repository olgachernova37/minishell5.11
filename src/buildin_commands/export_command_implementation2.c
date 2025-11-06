/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command_implementation2.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:50:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/06 15:08:48 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	only_export(t_env *env)
{
	char	**array;
	int		size;

	if (!env)
	{
		printf("declare -x\n");
		return (0);
	}
	size = count_env_ls(env);
	if (size == 0)
		return (0);
	array = fill_export_array(env, size);
	if (!array)
		return (1);
	array = bubble_sort(array, size);
	return (print_and_free_array(array));
}

size_t	joined_array_len(char **str)
{
	size_t	len;
	int		i;

	len = 0;
	i = 0;
	while (str[i])
	{
		len += ft_strlen(str[i]);
		if (str[i + 1])
			len += 1;
		i++;
	}
	return (len);
}

void	print_array_error(char **str)
{
	int	i;

	i = 0;
	ft_fprintf(STDERR_FD, "minishell: export: '");
	while (str[i])
	{
		ft_fprintf(STDERR_FD, "%s", str[i]);
		if (str[i + 1] != NULL)
		{
			ft_fprintf(STDERR_FD, " ");
		}
		i++;
	}
	ft_fprintf(STDERR_FD, "': not a valid identifier\n");
}

int	check_export_form(const char *input)
{
	const char	*eq;

	eq = ft_strchr(input, '=');
	if (!eq)
		return (0);
	else if (*(eq + 1) == '\0')
		return (1);
	else
		return (2);
}

int	only_var(char *input, t_env **env)
{
	t_env	*tmp;
	t_env	*new_node;

	if (!env)
		return (1);
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, input) == 0)
			return (0);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (1);
	new_node->key = ft_strdup(input);
	new_node->value = ft_strdup("");
	new_node->next = NULL;
	if (!*env)
		*env = new_node;
	else
		tmp->next = new_node;
	return (0);
}
