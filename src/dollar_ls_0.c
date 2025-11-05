/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_ls_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtereshc <dtereshc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:50:33 by dtereshc          #+#    #+#             */
/*   Updated: 2025/11/02 14:20:06 by dtereshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// creats t_xtnd node
t_xtnd	*xtnd_env(char *input, t_env **env)
{
	t_xtnd	*node;
	t_env	*current;

	current = *env;
	node = malloc(sizeof(t_xtnd));
	if (!node)
		exit(2);
	node->new = NULL;
	node->next = NULL;
	node->og_len = 0;
	node->len_dif = 0;
	while (current)
	{
		if (env_cmp(current->key, input))
		{
			node->og_len = ft_strlen(current->key) + 1;
			node->new = ft_strdup(current->value);
			node->len_dif = ft_strlen(node->new) - node->og_len;
			return (node);
		}
		current = current->next;
	}
	return (node);
}

t_xtnd	*create_g_exit_status_node(int g_exit_status)
{
	t_xtnd	*node;
	char	*status_str;

	node = malloc(sizeof(t_xtnd));
	if (!node)
		exit(2);
	status_str = ft_itoa(g_exit_status);
	if (!status_str)
		exit(2);
	node->new = status_str;
	node->next = NULL;
	node->og_len = 2;
	node->len_dif = ft_strlen(status_str) - 2;
	return (node);
}

t_xtnd	*crt_xtnd_ex_status(t_quote_state *st)
{
	t_xtnd	*xtnd_node;

	if (!st)
		exit(13);
	xtnd_node = create_g_exit_status_node(g_exit_status);
	if (!xtnd_node)
		exit(41);
	return (xtnd_node);
}

// finds out if $ENV has value
int	env_cmp(const char *key, const char *input)
{
	while (*key && (*key == *input))
	{
		input++;
		key++;
	}
	if (*key == '\0')
	{
		if (is_delimiter(*input))
			return (1);
		else if (*input == '\0')
			return (1);
		else if (!(is_delimiter(*input)))
			return (0);
	}
	return (0);
}

void	put_value(char *new_input, t_xtnd *ls, int n)
{
	int	i;

	i = 0;
	if (!new_input || !ls)
		exit(11);
	while (ls->new[i])
	{
		new_input[n + i] = ls->new[i];
		i++;
	}
}
