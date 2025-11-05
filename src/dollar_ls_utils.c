/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_ls_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtereshc <dtereshc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:39:51 by dtereshc          #+#    #+#             */
/*   Updated: 2025/11/02 14:20:44 by dtereshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_state_sttc(t_quote_state *state)
{
	if (!state)
		return ;
	state->closed = 0;
	state->inquotes = 0;
	state->new_pair = 0;
	state->type = '\0';
}

char	*crt_nd_new(int len, char *input)
{
	char	*new;
	int		n;

	n = 0;
	if (!input)
		exit(9);
	new = malloc(sizeof(char) * (len + 1));
	while (n < len)
	{
		new[n] = input[n];
		n++;
	}
	new[n] = '\0';
	return (new);
}

// connects nodes of t_xtnd linked ls
void	connect_nodes(t_xtnd **head, t_xtnd *node)
{
	t_xtnd	*tmp;

	tmp = *head;
	if (!node || !head)
		exit(22);
	if (*head == NULL)
	{
		*head = node;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = node;
}

// calcs lenght of OG $ENV accurance within original input
int	calc_og(char *input)
{
	int	i;

	i = 1;
	while (*input && !(is_delimiter(*input)))
	{
		input++;
		i++;
	}
	return (i);
}

// calcs length to add to OG_input lenght for extented *new_input
int	calc_len_dif(t_xtnd *head)
{
	t_xtnd	*tmp;
	int		len_dif;

	len_dif = 0;
	if (!head)
		exit(33);
	tmp = head;
	while (tmp != NULL)
	{
		len_dif += tmp->len_dif;
		tmp = tmp->next;
	}
	return (len_dif);
}
