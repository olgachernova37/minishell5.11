/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmnd_ls_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:36:59 by dtereshc          #+#    #+#             */
/*   Updated: 2025/11/04 13:59:24 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_input	*skip_redirection_tokens(t_input *tmp)
{
	if (tmp->type == TOKEN_RDR_IN || tmp->type == TOKEN_RDR_OUT
		|| tmp->type == TOKEN_APPND || tmp->type == TOKEN_HERE)
	{
		tmp = tmp->next;
		if (tmp)
			tmp = tmp->next;
	}
	return (tmp);
}

static void	fill_command_array(t_input *words, char **res, int size)
{
	t_input	*tmp;
	int		i;

	i = 0;
	tmp = words;
	while (tmp != NULL && tmp->type != TOKEN_PIPE && i < size)
	{
		if (tmp->type == TOKEN_RDR_IN || tmp->type == TOKEN_RDR_OUT
			|| tmp->type == TOKEN_APPND || tmp->type == TOKEN_HERE)
			tmp = skip_redirection_tokens(tmp);
		else
		{
			res[i++] = tmp->word;
			tmp = tmp->next;
		}
	}
	res[i] = NULL;
}

void	do_cmnd_array(t_input *words, t_cmnd *node, int size)
{
	char	**res;

	if (words == NULL)
		return ;
	res = malloc(sizeof(char *) * (size + 1));
	if (res == NULL)
		exit(1);
	fill_command_array(words, res, size);
	node->argv = res;
}

// returns malloced array of one command
// chage to ft_strdup(tmp->word); for right free(t_input) work
void	do_full_cmnd_array(t_input *words, t_cmnd *node, int size)
{
	int		i;
	t_input	*tmp;
	char	**res;

	if (words == NULL)
		return ;
	i = 0;
	tmp = words;
	res = malloc(sizeof(char *) * (size + 1));
	if (res == NULL)
		exit(1);
	while (tmp != NULL && tmp->type != TOKEN_PIPE)
	{
		res[i++] = tmp->word;
		tmp = tmp->next;
	}
	res[i] = NULL;
	node->full_argv = res;
}

// makes array of each token type of every cmnd token
void	do_cmnd_array_type(t_input *words, t_cmnd *node, int size)
{
	int				i;
	t_input			*tmp;
	t_token_type	**res_type;

	i = 0;
	if (words == NULL)
		return ;
	tmp = words;
	res_type = malloc(sizeof(t_token_type *) * (size + 1));
	if (res_type == NULL)
		exit(1);
	while (tmp != NULL)
	{
		if (tmp->type == TOKEN_PIPE)
		{
			node->pipe = true;
			break ;
		}
		res_type[i++] = &tmp->type;
		tmp = tmp->next;
	}
	res_type[i] = NULL;
	node->argv_type = res_type;
}
