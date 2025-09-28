/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ep <ep@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:31:03 by erpascua          #+#    #+#             */
/*   Updated: 2025/09/29 00:29:05 by ep               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <string.h>
# include <term.h>

extern int				g_received_signal;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef enum e_builtin_type
{
	BI_NONE,
	BI_ECHO,
	BI_CD,
	BI_PWD,
	BI_EXPORT,
	BI_UNSET,
	BI_ENV,
	BI_EXIT,
	NB_BUILTINS
}						t_builtin_type;

typedef enum e_token
{
	WORD,
	REDIR,
	PIPE,
	OPERATOR,
	NB_TOKENS
}						t_token;

typedef enum e_subtoken
{
	NONE,
	HEREDOC,
	APPEND,
	IN,
	OUT,
	AND,
	OR,
	QUOTE,
	NB_SUBTOKENS
}						t_subtoken;

typedef enum e_group
{
	G_REDIR_IN,
	G_REDIR_OUT,
	G_REDIR_HEREDOC,
	G_REDIR_APPEND,
	G_CMD,
	G_PIPE,
	G_INVALID,
	NB_GROUPS
}						t_group;

typedef struct s_stack
{
	char				*content;
	bool				is_expandable;
	bool				is_append;
	t_token				token;
	t_subtoken			sub_token;
	struct s_stack		*next;
}						t_stack;

typedef struct s_cmd
{
	char				**args;
	char				*path;
	t_builtin_type		builtin_type;
}						t_cmd;

typedef struct s_data
{
	t_cmd				cmd;
	char				*file_or_limiter;
	t_group				group;
	struct s_data		*next;
}						t_data;

typedef struct s_paths
{
	char				*pwd;
	char				*oldpwd;
	char				*home;
	bool				has_home;
	bool				has_oldpwd;
}						t_paths;

typedef struct s_inout
{
	char				*file_or_limiter;
	int					fd;
	int					unused_fd;
	t_group				type;
	struct s_inout		*next;
}						t_inout;

t_inout					*alloc_pipe_inout(void);
t_inout					*alloc_redir_inout(t_data *data);
void					print_inout(t_inout *inout);

typedef struct s_process
{
	t_cmd				cmd;
	t_list				*inputs;
	t_list				*outputs;
	pid_t				pid;
	struct s_process	*next;
}						t_process;

typedef struct s_msh
{
	t_env				*env;
	char				*entry;
	t_stack				*stack;
	char				*history;
	t_token				*token_type;
	t_data				*data;
	bool				is_heredoc;
	bool				is_expandable;
	bool				is_append;
	char				*builtin_names[NB_BUILTINS];
	int					(*builtin_funcs[NB_BUILTINS])(struct s_msh *, char **);
	t_paths				paths;
	int					exit_code;
	int					nb_cmd;
}						t_msh;

int						launch_program(t_msh *msh);
void					print_banner(void);
int						struct_init(t_msh *msh);
void					save_env(t_msh *msh, char **env);
// LEXER
int						lexer(t_msh *msh);
char					*read_entry(t_msh *msh, char *s, int *i);
// LEXER UTILS
bool					is_delimeter(char c);
bool					is_redirection(char c);
bool					is_operator(char c);
bool					is_pipe(char c);
void					check_redirection(char *s, int *i);
// TOKEN HANDLERS
int						handle_quotes(char *s, int *i, char quote_char);
void					handle_word(char *s, int *i);
char					*extract_word(t_msh *msh, char *s, int start, int end);
// STACK UTILS
void					print_stack(t_stack *s);
void					add_word_to_stack(t_msh *msh, char *word);
t_stack					*stack_last(t_stack *s);
// ADDING TO STACK
void					fill_node(t_msh *msh, char *word);
t_stack					*new_stack(char *content);
int						fill_stack(t_stack **a, char *word);
void					stack_destroy(t_stack *head);
void					stack_add_back(t_stack **s, t_stack *new_s);
t_stack					*copy_node_stack(t_stack *stack, char *s);
// TOKEN
int						identify_token(t_msh *msh);

// TOKEN VALIDATION
bool					check_heredoc_append(t_stack *s);
bool					check_in_out(t_stack *s);
bool					is_valid_redir(t_stack *s);
bool					is_valid_operator(t_stack *s);
bool					is_valid_pipe(t_stack *s);
// TOKEN CLASSIFICATION
bool					is_redir_symbol(t_stack *s);
bool					is_operation_symb(t_stack *s);
int						handle_redirection_token(t_msh *msh, t_stack *tmp);
int						handle_operator_token(t_msh *msh, t_stack *tmp);
int						classify_single_token(t_msh *msh, t_stack *tmp);
// PARSING
int						parse(t_msh *msh);
size_t					get_env_var_len(char *word);
char					*my_getenv(t_msh *msh, char *word);
int						add_command_node(t_msh *msh, t_stack **tmp,
							t_data *new_node);
char					*cmd_path(t_msh *msh, char *cmd);
int						set_up_path(t_msh *msh, t_data *data);
int						add_redir_node(t_msh *msh, t_stack **tmp,
							t_data *new_node);
t_data					*init_data_node(t_msh *msh);
t_data					*data_add_back(t_data *data, t_data *new);
t_process				*pre_exec(t_msh *msh);
// EXPAND
char					*expand(t_msh *msh, char *s);
// BUILT-IN
t_builtin_type			get_builtin_type(t_msh *msh, t_data *data);
bool					execute_builtin(t_msh *msh, t_process *process);
int						bi_exit(t_msh *msh, char **argv);
int						bi_echo(t_msh *msh, char **argv);
int						bi_cd(t_msh *msh, char **argv);
bool					cd_home(t_msh *msh, t_env *env, t_paths *paths);
bool					cd_oldpwd(t_msh *msh, t_env *env, t_paths *paths);
bool					cd_folder(t_msh *msh, t_env *env, t_paths *paths,
							char *folder);
void					cd_get_paths(t_env *env, t_paths *paths);
void					cd_update_env(t_env *env, t_paths *paths);
void					cd_error(t_msh *msh, char *path);
int						bi_pwd(t_msh *msh, char **argv);
int						bi_export(t_msh *msh, char **argv);
bool					is_valid_identifier(char *s);
bool					build_env_entry_with_value(char **env_to_sort,
							t_env *tmp, int i);
bool					build_env_entry_no_value(char **env_to_sort, t_env *tmp,
							int i);
void					sort_env_array(char **env_to_sort, int len);
void					print_and_free_array(char **env_to_sort, int len);
void					order_tab(char **env_to_sort, int len);
int						lst_len(t_env *env);
bool					export_replace_value(t_env *env, t_env *new_node);
t_env					*create_env_node_no_value(char *key);
bool					export_replace_value_no_val(t_env *env, char *key);
void					export_create_keyvalue(t_msh *msh, t_env *new_node);
void					export_var_with_value(t_msh *msh, char *arg);
int						bi_unset(t_msh *msh, char **argv);
int						bi_env(t_msh *msh, char **argv);
t_env					*create_env_node(char *env_line);
void					clean_exit(t_msh *msh, char *s);
void					free_env_list(t_env *env);
// SIGNALS
bool					is_eof(void);
void					sigint_handler(int process);
void					sigint_silent_handler(int signum);
// FREE
void					free_data(t_data *data);
void					ft_free(t_msh *msh);
void					data_destroy(t_data *head);
// UTILS
char					**msh_getenv(t_msh *msh);
int						len_string_array(char **s);
char					**string_array_copy(char **s);
void					print_data(t_msh *msh);
void					print_pre_exec(t_process *process);
char					**string_array_concat(char **sa1, char **sa2);
// EXEC
void					execute_all(t_msh *msh, t_process *process);
// FREE
void					free_msh(t_msh *msh);
void					env_destroy(t_env *env);
void					free_msh_builtins(t_msh *msh);

#endif