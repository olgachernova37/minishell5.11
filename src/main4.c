/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/06 14:07:35 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	setup_exit_cleanup(t_cleanup *cleanup, t_env **env, char **env_array)
{
	cleanup->env = env;
	cleanup->env_array = env_array;
	cleanup->cmnd_ls = NULL;
	cleanup->words = NULL;
	cleanup->raw_input = NULL;
}
