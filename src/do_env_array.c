/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_env_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:43:27 by dt                #+#    #+#             */
/*   Updated: 2025/11/04 21:43:14 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*strjoin_modified(char const *s1, char const *s2)
{
	char	*new;
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlenn(s1);
	len2 = ft_strlenn(s2);
	new = malloc(sizeof(char) * (len1 + len2 + 2));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len1)
	{
		new[i] = s1[i];
		i++;
	}
	new[i++] = '=';
	while (j < len2)
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}

char	**do_env_array(t_env *env, int size)
{
	t_env	*tmp;
	char	**res;
	int		i;

	if (size < 0)
		return (NULL);
	res = malloc(sizeof(char *) * (size + 1));
	if (!res)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp != NULL && i < size)
	{
		res[i++] = strjoin_modified(tmp->key, tmp->value);
		tmp = tmp->next;
	}
	res[i] = NULL;
	return (res);
}

int	count_env_ls(t_env *env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	if (env == NULL)
		return (0);
	tmp = env;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
