/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:28:29 by dt                #+#    #+#             */
/*   Updated: 2025/11/06 13:40:49 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env_fields(t_env *env)
{
	if (!env)
		return ;
	free(env->key);
	free(env->value);
}

void	free_env(t_env **env)
{
	t_env	*tmp;
	t_env	*prev;

	if (!env || !*env)
		return ;
	tmp = *env;
	while (tmp != NULL)
	{
		prev = tmp;
		free_env_fields(tmp);
		tmp = tmp->next;
		free(prev);
	}
	*env = NULL;
}

void	free_xtnds(t_xtnd **xtnds)
{
	t_xtnd	*tmp;
	t_xtnd	*prev;

	if (!xtnds || !*xtnds)
		return ;
	tmp = *xtnds;
	while (tmp)
	{
		prev = tmp;
		free(tmp->new);
		tmp = tmp->next;
		free(prev);
	}
	*xtnds = NULL;
}

void	free_t_input(t_input **input)
{
	t_input	*nxt;
	t_input	*cur;

	if (!input || !*input)
		return ;
	cur = *input;
	while (cur)
	{
		nxt = cur->next;
		free(cur->word);
		free(cur);
		cur = nxt;
	}
	*input = NULL;
}

void	free_argv_type(t_cmnd *cmnd_node)
{
	if (!cmnd_node || !cmnd_node->argv_type)
		return ;
	free(cmnd_node->argv_type);
	cmnd_node->argv_type = NULL;
}

