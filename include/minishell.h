/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:31:03 by erpascua          #+#    #+#             */
/*   Updated: 2025/09/08 14:09:36 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <term.h>

extern int			g_exit_code;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef enum e_builtin
{
	BI_ECHO,
	BI_CD,
	BI_PWD,
	BI_EXPORT,
	BI_UNSET,
	BI_ENV,
	BI_EXIT,
	NB_BUILTINS
}					t_builtin;

typedef enum e_token
{
	WORD,
	REDIR,
	PIPE,
	OPERATOR,
	NB_TOKENS
}					t_token;

typedef enum e_subtoken
{
	NONE,
	HEREDOC,
	APPEND,
	IN,
	OUT,
	AND,
	OR,
	DQUOTE,
	NB_SUBTOKENS
}					t_subtoken;

typedef enum e_group
{
	G_REDIR,
	G_CMD,
	G_PIPE,
	G_OPERATOR,
	NB_GROUPS
}					t_group;

typedef struct s_stack
{
	char			*content;
	t_token			token;
	t_subtoken		sub_token;
	struct s_stack	*next;
}					t_stack;

typedef struct s_data
{
	char			**cmd;
	char			**redir;
	char			*operator;
	t_group			group;
	struct s_data	*next;
}					t_data;

typedef struct s_msh
{
	t_env			*env;
	char			*entry;
	t_stack			*stack;
	char			*history;
	t_token			*token_type;
	t_data			*data;
	bool			is_heredoc;
	bool			is_builtin;
	char			*builtin_names[NB_BUILTINS];
	int				(*builtin_funcs[NB_BUILTINS])(void);
}					t_msh;

int					launch_program(t_msh *msh);
void				print_banner(void);
int					struct_init(t_msh *msh);
// LEXER
int					lexer(t_msh *msh);
char				*read_entry(char *s, int *i);
// LEXER UTILS
bool				is_delimeter(char c);
bool				is_redirection(char c);
bool				is_operator(char c);
void				check_redirection(char *s, int *i);
void				check_operator(char *s, int *i);
// TOKEN HANDLERS
int					handle_quotes(char *s, int *i, char quote_char);
void				handle_word(char *s, int *i);
char				*extract_word(char *s, int start, int end);
// STACK UTILS
void				print_stack(t_stack *s);
void				add_word_to_stack(t_msh *msh, char *word);
// ADDING TO STACK
void				fill_node(t_msh *msh, char *word);
t_stack				*new_stack(char *content);
int					fill_stack(t_stack **a, char *word);
void				stack_destroy(t_stack *head);
void				stack_add_back(t_stack **s, t_stack *new_s);
// TOKEN
int					identity_token(t_msh *msh);
// TOKEN VALIDATION
bool				check_heredoc_append(t_stack *s);
bool				check_in_out(t_stack *s);
bool				is_valid_redir(t_stack *s);
bool				is_valid_operator(t_stack *s);
bool				is_valid_pipe(t_stack *s);
// TOKEN CLASSIFICATION
bool				is_redir_symbol(t_stack *s);
bool				is_operation_symb(t_stack *s);
void				handle_redirection_token(t_stack *tmp);
void				handle_operator_token(t_stack *tmp);
void				classify_single_token(t_stack *tmp);
// PARSING
int					parse(t_msh *msh);
// BUILT-IN
bool				is_builtin(t_msh *msh);
int					bi_exit(void);
int					bi_echo(void);
int					bi_cd(void);
int					bi_pwd(void);
int					bi_export(void);
int					bi_unset(void);
int					bi_env(void);
// SIGNALS
bool				is_eof(void);
void				sigint_handler(int process);

#endif
