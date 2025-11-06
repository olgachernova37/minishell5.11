/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:31:21 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/06 13:55:06 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL2_H
# define MINISHELL2_H

# include "libs/libft/libft.h"
# include "libs/libftprintf/ft_printf.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

typedef enum e_tokens			t_token_type;

typedef struct s_cmnd			t_cmnd;

typedef struct s_input			t_input;

typedef struct s_rdrs			t_rdrs;

typedef struct s_quote_state	t_quote_state;

typedef struct s_xtnd			t_xtnd;

typedef struct s_len_type_qts	t_len_type_qts;

typedef struct s_env			t_env;

t_input							*tokenize(t_input *words, char *input);

t_input							*do_node(t_len_type_qts *ltq, char *input);

t_xtnd							*crt_xtnd_ls(char *input, t_env **env);

t_cmnd							*what_cmnd_shrt_0(t_cmnd *cmnd,
									int stdin_backup, int stdout_backup);

t_env							*create_env_node(char *key, char *input);

int	(*allocate_fds(t_cmnd **cmnd, int *pipes_qntt))[2];

#endif
