/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:31:03 by erpascua          #+#    #+#             */
/*   Updated: 2025/08/25 20:06:59 by gpollast         ###   ########.fr       */
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

typedef struct s_stack
{
	char			*content;
	char			*token;
	struct s_stack	*next;
}					t_stack;

typedef struct s_msh
{
	t_env			*env;
	char			*entry;
	t_stack			*stack;
	char			*history;
	bool			is_heredoc;
	bool			is_builtin;
	char			*builtin_names[NB_BUILTINS];
	int				(*builtin_funcs[NB_BUILTINS])(void);
}					t_msh;

int					launch_program(t_msh *msh);
void				print_banner(void);
void				struct_init(t_msh *msh);
// LEXER
int					lexer(t_msh *msh);
// ADDING TO STACK
void				fill_node(t_msh *msh, char *word);
t_stack				*new_stack(char *content);
int					fill_stack(t_stack **a, char *word);
void				stack_destroy(t_stack *head);
void				stack_add_back(t_stack **s, t_stack *new);
// TOKEN
void				identity_token(t_msh *msh);
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
