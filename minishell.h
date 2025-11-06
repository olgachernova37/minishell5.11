/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:31:21 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/06 13:33:58 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libs/libft/libft.h"
# include "libs/libftprintf/ft_printf.h"
# include "minishell2.h"
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

extern int			g_exit_status;

typedef enum e_tokens
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_RDR_IN,
	TOKEN_RDR_OUT,
	TOKEN_APPND,
	TOKEN_HERE,
	TOKEN_COMPLEX
}					t_token_type;

// cmnds structure
typedef struct s_cmnd
{
	char **argv;              // do_cmnd_array
	char **full_argv;         // do_full_cmnd_array
	t_token_type **argv_type; // do_cmnd_array_type
	struct s_rdrs *rdrs;      // free func is done
	int				fds[2];
	bool			appnd;
	bool			heredoc;
	bool			pipe;
	struct s_cmnd	*next;
}					t_cmnd;

// free func is made
// input tokens
typedef struct s_input
{
	t_token_type	type;
	char			*word;
	struct s_input	*next;
}					t_input;

// free func is made
// redirs linked list
typedef struct s_rdrs
{
	t_token_type	redir_type;
	char			*filename;
	struct s_rdrs	*next;
}					t_rdrs;

// don't know if free func is neede probably not
typedef struct s_quote_state
{
	char			type;
	int				inquotes;
	int				closed;
	int				new_pair;
}					t_quote_state;

// free func is made
typedef struct s_xtnd
{
	int				len_dif;
	int				og_len;
	char			*new;
	struct s_xtnd	*next;
}					t_xtnd;

// freed automatically within creat_tokenz();
// length type and quote type for every token
typedef struct s_len_type_qts
{
	int				len;
	int				type;
	int				qts;
}					t_len_type_qts;

// free func is made
// envar var
typedef struct s_env
{
	char			*key;
	char			*value;
	int				new_len;
	struct s_env	*next;
}					t_env;

// cleanup structure for exit command
typedef struct s_cleanup
{
	t_env			**env;
	char			**env_array;
	t_cmnd			**cmnd_ls;
	t_input			**words;
	char			**raw_input;
}					t_cleanup;

// free func in process
typedef struct s_redir_context
{
	char			*bad_char;
	int				*is_newline;
	int				in_q;
}					t_redir_context;

// tokenizer_utils_2.c
void				normalize_input_inplace(char *s);
int					is_shell_space(unsigned char c);

// main_utils.c
void				print_env(t_env *env);
void				print_og_env(char **envp);
void				print_cmnd_ls(t_cmnd *list);
void				print_input(t_input *list);
void				print_extened_input(char *s);

// creat_cmnd_list.c
t_input				*move_ptr_cmnd(t_input *next_cmnd);
void				set_apnd_hered_pipe(t_cmnd *node);
void				do_rdrs(t_cmnd *node);
t_cmnd				*setup_cmnd_node(t_cmnd *node, t_input *next_cmnd);
t_cmnd				*crt_cmnd_ls_lgc(int cmnd_qntt, t_cmnd *list,
						t_input *words);
t_cmnd				*crt_cmnd_ls(t_input *words);

// cmnd_ls_utils_0.c
void				set_to_zero(t_cmnd *cmnd_node);
int					count_cmnds(t_input *words);
int					count_cmnd_len(t_input *words);
int					count_cmnd_len_argv(t_input *words);

// cmnd_ls_utils_1.c
void				do_cmnd_array(t_input *words, t_cmnd *node, int size);
void				do_full_cmnd_array(t_input *words, t_cmnd *node, int size);
void				do_cmnd_array_type(t_input *words, t_cmnd *node, int size);

// validate_input.c
int					has_backslash(char *input);
int					has_simocolon(char *input);
int					has_double_and_or_pipe(char *input);
bool				validate_input(char *input);
int					skip_spaces(char *str);
int					has_invalid_pipe(char *input);
bool				validate_input(char *input);
int					is_redir_char(char c);
int					has_invalid_redirections(char *input, char *bad_char,
						int *is_newline);
void				update_quote_state(char c, int *in_q);
int					check_redirection_end(char *input, int i, char *bad_char,
						int *is_newline);
int					check_leading_redirection(char *input, char *bad_char,
						int *is_newline);
int					validate_redirections_loop(char *input, char *bad_char,
						int *is_newline);
int					process_redirection_in_loop(char *input, int *i,
						t_redir_context *ctx);

// validate_input_2.c
int					find_sq(char *input, int *signl_q);
int					find_dq(char *input, int *double_q);
int					has_unclosed_quotes(char *input);
bool				drop_false(char *error_message);

// tokenizer.c
int					creat_tokenz(char *input, t_input **words);
// t_input				*tokenize(t_input *words, char *input);
void				add_node(t_input **words, t_input *new_word);
// t_input				*do_node(t_len_type_qts *ltq, char *input);

// tokenizer_utils.c
t_len_type_qts		*tk_in_here(char *input, t_len_type_qts *ltq);
t_len_type_qts		*tk_out_appnd(char *input, t_len_type_qts *ltq);
t_len_type_qts		*tk_pipe(t_len_type_qts *ltq);
void				*do_node_clear(t_input *new_node);
void				end_do_node(t_len_type_qts *ltq, t_input *new_node,
						char *res);

// tokenizer_utils_2.c
t_len_type_qts		*tk_word(char *input, t_len_type_qts *ltq);
int					calc_len(t_input *new_word);
t_quote_state		*dtct_inquotes(char cr);
int					is_complex_wrd(t_len_type_qts *ltq, char *input);

// do_env_array.c
char				*strjoin_modified(char const *s1, char const *s2);
char				**do_env_array(t_env *env, int size);
int					count_env_ls(t_env *env);

// utils.c
int					is_delimiter(char c);
int					another_one(int i, char *input, t_quote_state *st);
int					if_logic(int i, char *input, t_quote_state *st);
void				ft_clean(t_input *words, char *input);
size_t				ft_strlenn(const char *s);

// dollar_ls_0.c
t_xtnd				*xtnd_env(char *input, t_env **env);
t_xtnd				*create_g_exit_status_node(int g_exit_status);
t_xtnd				*crt_xtnd_ex_status(t_quote_state *state);
int					env_cmp(const char *key, const char *input);
void				put_value(char *new_input, t_xtnd *ls, int n);

// dollar_ls_1.c
void				dollar_extend_logic(char *input, char *new_input,
						t_xtnd *xtnds, t_xtnd *head);
t_xtnd				*crt_xtnd_logic(char *input, t_env **env,
						t_quote_state *st);
char				*crt_nd_new(int len, char *input);
t_xtnd				*pst_q(char *input);
int					process_found_redirection(char *input, int *i,
						t_redir_context *ctx);

char				*dollar_extend(char *input, t_env **env);

// dollar_ls_utils.c
void				reset_state_sttc(t_quote_state *state);
void				connect_nodes(t_xtnd **head, t_xtnd *node);
int					is_delimiter(char c);
int					calc_og(char *input);
int					calc_len_dif(t_xtnd *head);

// echo_command_implementation.c
int					echo_command_implementation(t_cmnd **cmnd_ls);
bool				is_command_buildin(char **input);
void				secure_fd(int stdin_backup, int stdout_backup);

// what_command.c
t_cmnd				*skip_cmnds(t_cmnd *cmnd);

// t_cmnd				*what_cmnd_shrt_0(t_cmnd *cmnd,int stdin_backup,
// 						int stdout_backup);
void				what_cmnd_shrt_1(t_cmnd *cmnd, t_env **env,
						char **env_array, t_cleanup *cleanup);
void				what_command(t_cmnd **cmnd_ls, t_env **my_env,
						char **array_env, t_cleanup *cleanup);

// what_command_utils.c

int					match_buildin(char *og_input, char *match_cmnd);
int					which_buildin_command(t_cmnd *cmnd, t_env **my_env,
						char **env_array, t_cleanup *cleanup);

// pwd_command_implementation.c
int					pwd_command_implementation(void);

// cd_command_implementation.c
int					cd_command_implementation(char **input, t_env *my_env);

// cd
void				change_pwd(t_env *env);
void				change_oldpwd(t_env *env);
void				print_pwd_and_oldpwd(t_env *env);
int					only_cd(t_env *env);
char				*get_env_value(t_env *env, const char *key);
void				update_env_value(t_env *env, const char *key,
						const char *new_value);
int					change_to_oldpwd(char *path, char *prev_dir, char *cwd);
int					previous_dir(t_env *env);

// export_command_implementation.c functions
int					get_array_size(char **array);
char				**bubble_sort(char **array, int size);
int					print_and_free_array(char **array);
char				*get_env_string(t_env *tmp);
char				**fill_export_array(t_env *env, int size);
int					only_export(t_env *env);
size_t				joined_array_len(char **str);
void				print_array_error(char **str);
int					check_export_form(const char *input);
int					only_var(char *input, t_env **env);
char				*input_parse_key_export(char *input);
char				*input_parse_value_export(char *input);
// t_env				*create_env_node(char *key,char *input);
int					update_existing_env(t_env *tmp, char *key, char *input);
int					add_new_node_ex(t_env **env, t_env *tmp, char *key,
						char *input);
int					var_and_value(char *input, t_env **env);
t_env				*create_empty_node(char *key);
int					update_existing_empty(t_env *tmp, char *key);
int					var_and_equal(char *input, t_env **env);
int					one_var(char *input, t_env **env);
int					is_two_var(char **input);
int					two_var(char **input, t_env **env);
int					parsing_export(char **input, t_env **env);

// env
t_env				*env_init(char **envp);
void				print_my_env(t_env *env);

// Updated function declarations
int					export_command_implementation(char **input, t_env **env);
int					unset_command_implementation(t_env **env, char **input);
int					exit_command_implementation(char **input,
						t_cleanup *cleanup);
int					other_commands_implementation(char **input, t_env **env);

// pipes.c
int					finish_child(t_cmnd **cmnd, int pipes_qntt, pid_t *pids,
						int i);
void				child_logic(t_cmnd **cmnd, t_cmnd *cur_cmnd,
						t_cleanup *cleanup);
int					creat_child(int pipes_qntt, t_cmnd **cmnd,
						t_cleanup *cleanup);
int					do_pipeline(t_cmnd **cmnd, t_cleanup *cleanup);

// pipes_utils_0.c
int					is_pipeline(t_cmnd **cmnd);
int					close_fds(int pipes_qntt, int (*fds)[2]);
void				close_ends(t_cmnd **cmnd);
void				connect_ends(t_cmnd *cmnd);
int					pid_err(pid_t *pids, int i);

// pipes_utils_1.c
// int (*allocate_fds(t_cmnd **cmnd, int *pipes_qntt))[2];
void				piping(int pipes, int (*fds)[2]);
void				connect_ends(t_cmnd *cmnd);
void				connect_fds(t_cmnd **cmnd, int pipes_qntt, int (*fds)[2]);
int					execve_child(t_cmnd *cmnd, t_env **my_env,
						char **array_env);
int					find_last_state(pid_t *pids, int i, int pipes_qntt);

// signal.c
void				handler_sig_int(int sig);
void				handler_sig_quit(int sig);
int					exit_func(void);
void				init_signals(void);

/* other_comands.c*/
void				free_split(char **split);
char				*get_path_from_env(t_env **env);
char				**input_with_null_terminator(char **input);
char				*find_command_path(char **input, t_env **env);
int					execute_command(char *path_with_command, char **input,
						t_env **env);
int					handle_direct_path_command(char **input, t_env **env);
int					other_commands_implementation(char **input, t_env **env);
int					handle_path_command(char **input, t_env **env);
int					wait_and_handle(pid_t pid, int *status, char **new_input);
int					spawn_child(char *path_with_command, char **new_input,
						pid_t *pid);
void				parent_prepare_signals(void);
int					parent_wait_and_cleanup(pid_t pid, char **new_input);
void				child_exec(char *path_with_command, char **new_input,
						char **env_array);
int					handle_child_exit(int status);
void				setup_child_signals(void);

// parsing.c
char				*extract_word(char *input, t_len_type_qts *ltq);
t_input				*alloc_new_node(void);

// Redirections implementation
int					handle_input_redir(t_rdrs *rdr);
int					handle_output_redir(t_rdrs *rdr);
int					handle_append_redir(t_rdrs *rdr);
int					handle_heredoc_redir(t_rdrs *rdr, int counter);
int					process_single_redir(t_rdrs *rdr);
int					implamentation_redir(t_cmnd *cmnd);
int					process_heredocs_for_command(t_rdrs *rdr_list);
int					has_heredocs(t_rdrs *rdr_list);

// Heredoc implementation
char				*get_heredoc_filename(int counter);
char				*create_base_filename(char *pid_str);
void				heredoc_signal_handler(int sig);
int					write_heredoc_content(int fd, char *delimiter);
int					handle_heredoc(char *delimiter, int counter);

// From implem_redir2.c
int					process_one_heredoc(int counter, int *last_heredoc_fd);
int					count_heredocs_in_command(t_rdrs *rdr_list);

// From implem_redir3.c
int					handle_non_heredoc_redir(t_rdrs *rdr, int *heredoc_fd);
int					setup_heredoc_input(int *heredoc_fd);
int					process_redirections_loop(t_rdrs *rdr_list,
						int *heredoc_fd);

void				free_filename(char *filename);
int					check_delimiter_match(char *line, char *delimiter,
						size_t delim_len);
int					handle_heredoc_exit_conditions(char *line, char *delimiter);

void				free_command_arrays(t_cmnd *cmd);
void				free_redirections(t_rdrs *rdrs);
int					process_all_heredocs_in_pipeline(t_cmnd *cmnd_list);
void				cleanup_all_heredocs(t_cmnd *cmnd_list);

// free_funcs_0.c
void				free_full_argv(t_cmnd *cmnd_node);
void				*do_node_clear(t_input *new_node);
void				free_rdrs(t_rdrs *rdrs);
void				free_argv_head(t_cmnd *cmnd_node);
void				free_cmnd_ls(t_cmnd **cmnd, t_input **words);

// free_funcs_1.c
void				free_env_fields(t_env *env);
void				free_env(t_env **env);
void				free_rdrs(t_rdrs *rdrs);
void				free_xtnds(t_xtnd **xtnds);
void				free_t_input(t_input **input);
void				free_argv_type(t_cmnd *cmnd_node);
void				free_env_array(char **env_array);
int					other_commands_implementation(char **input, t_env **env);
void				child_logic(t_cmnd **cmnd, t_cmnd *cur_cmnd,
						t_cleanup *cleanup);
void				free_child_structures(t_cmnd **cmnd, t_cleanup *cleanup,
						t_cmnd *keep);
void				free_current_cmnd(t_cmnd *cur_cmnd);
char				*read_line_with_prompt(const char *prompt, int is_tty);
void				initialize_shell(t_env **env, char ***env_array,
						char **envp);
void				process_command_pipeline(char *input, t_env **env,
						char **env_array);
int					handle_empty_input(char *input);
void				free_child_structures(t_cmnd **cmnd, t_cleanup *cleanup,
						t_cmnd *keep);
void	cleanup_and_exit(t_cmnd **cmnd, t_cleanup *cleanup, int exit_code);

#endif
