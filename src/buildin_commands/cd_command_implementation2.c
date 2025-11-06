/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command_implementation2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 20:42:50 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/06 13:07:12 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env_value(t_env *env, const char *key, const char *new_value)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(new_value);
			break ;
		}
		tmp = tmp->next;
	}
}

int	change_to_oldpwd(char *path, char *prev_dir, char *cwd)
{
	if (!getcwd(prev_dir, PATH_MAX))
		return (perror("getcwd"), 1);
	if (chdir(path) == -1)
		return (perror("cd"), 1);
	if (getcwd(cwd, PATH_MAX))
		printf("%s\n", cwd);
	else
		perror("getcwd");
	return (0);
}

int	previous_dir(t_env *env)
{
	char	*path;
	char	cwd[PATH_MAX];
	char	prev_dir[PATH_MAX];

	path = get_env_value(env, "OLDPWD");
	if (!path || !*path)
		return (printf("cd: OLDPWD not set\n"), 1);
	if (change_to_oldpwd(path, prev_dir, cwd) != 0)
		return (1);
	update_env_value(env, "OLDPWD", prev_dir);
	update_env_value(env, "PWD", cwd);
	return (0);
}

int	standard_cd(char **input, t_env *env)
{
	char	*path;

	path = input[1];
	change_oldpwd(env);
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	change_pwd(env);
	return (0);
}

int	cd_command_implementation(char **input, t_env *env)
{
	int	i;

	i = 1;
	if (input[i] == NULL)
	{
		return (only_cd(env));
	}
	else if ((input[i] != NULL) && (input[i + 1] == NULL))
	{
		if (ft_strcmp(input[i], "-") == 0)
			return (previous_dir(env));
		else if (ft_strcmp(input[i], "~") == 0)
			return (only_cd(env));
		else
			return (standard_cd(input, env));
	}
	else
	{
		fprintf(stderr, "cd: too many arguments\n");
		return (1);
	}
	return (0);
}
