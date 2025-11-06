/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_ls_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:54:13 by dtereshc          #+#    #+#             */
/*   Updated: 2025/11/06 13:12:26 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dollar_extend_logic(char *input, char *new_input, t_xtnd *xtnds,
		t_xtnd *head)
{
	t_quote_state	*st;
	int				i;
	int				n;

	i = 0;
	n = 0;
	while (input[i])
	{
		st = dtct_inquotes(input[i]);
		if (if_logic(i, input, st) || another_one(i, input, st))
		{
			put_value(new_input, xtnds, n);
			n += ft_strlen(xtnds->new);
			i += xtnds->og_len;
			xtnds = xtnds->next;
		}
		else
			new_input[n++] = input[i++];
	}
	new_input[n] = '\0';
	reset_state_sttc(st);
	free_xtnds(&head);
}

t_xtnd	*crt_xtnd_logic(char *input, t_env **env, t_quote_state *st)
{
	t_xtnd	*xtnd_node;

	xtnd_node = xtnd_env(input, env);
	if (!xtnd_node)
		exit(41);
	if (!xtnd_node->new)
	{
		if (*(input) == '?')
		{
			free_xtnds(&xtnd_node);
			xtnd_node = crt_xtnd_ex_status(st);
		}
		else
		{
			xtnd_node->new = ft_strdup("");
			xtnd_node->og_len = calc_og(input);
			if (*(xtnd_node->new) == 0)
				xtnd_node->len_dif = ft_strlen(xtnd_node->new)
					- xtnd_node->og_len;
		}
	}
	return (xtnd_node);
}

t_xtnd	*pst_q(char *input)
{
	t_xtnd	*node;
	int		len;

	len = 0;
	node = malloc(sizeof(t_xtnd));
	if (!node)
		exit(2);
	while (*(input + len) != '\'' && *(input + len) != '"')
		len++;
	node->og_len = len + 3;
	node->new = crt_nd_new(len, input);
	node->len_dif = ft_strlen(node->new) - node->og_len;
	node->next = NULL;
	return (node);
}

char	*dollar_extend(char *input, t_env **env)
{
	t_xtnd	*xtnds;
	t_xtnd	*head;
	char	*new_input;

	if (!input || !env)
		return (NULL);
	xtnds = crt_xtnd_ls(input, env);
	if (!xtnds)
		return (ft_strdup(input));
	head = xtnds;
	new_input = malloc(sizeof(char) * (ft_strlen(input) + calc_len_dif(xtnds)
				+ 1));
	if (!new_input)
	{
		free_xtnds(&head);
		return (ft_strdup(input));
	}
	dollar_extend_logic(input, new_input, xtnds, head);
	return (new_input);
}
