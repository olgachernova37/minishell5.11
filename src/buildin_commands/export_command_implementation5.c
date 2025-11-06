/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command_implementation5.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:50:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/06 13:10:23 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_two_var(char **input)
{
	int	count;

	count = 0;
	if (!input)
		return (0);
	while (input[count])
		count++;
	return (count);
}

int	two_var(char **input, t_env **env)
{
	int	result1;
	int	result2;

	result1 = one_var(input[1], env);
	result2 = one_var(input[2], env);
	if (result1 != 0)
		return (result1);
	return (result2);
}

int	is_minus_in_export_name(char **input)
{
	int		i;
	char	*s;

	if (!input || !input[1])
		return (0);
	s = input[1];
	i = 0;
	while (s[i] && s[i] != '=')
	{
		if (s[i] == '-')
			return (1);
		i++;
	}
	return (0);
}

int	parsing_export(char **input, t_env **env)
{
	if ((input[1][0] >= '0' && input[1][0] <= '9') || ft_strchr(input[1], '+')
		|| input[1][0] == '=' || is_minus_in_export_name(input))
	{
		print_array_error(input);
		return (1);
	}
	else if (is_two_var(input) > 2)
	{
		return (two_var(input, env));
	}
	else
	{
		return (one_var(input[1], env));
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
