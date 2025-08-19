/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:31:03 by erpascua          #+#    #+#             */
/*   Updated: 2025/08/22 11:56:19 by erpascua         ###   ########.fr       */
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

extern int			g_exit_code;
// DEV: Eric: J'ai creer une premiere structure qui reprend le path de pipex
// et qui nous permettra de faire quelques tests. Au moment je redige ceci
// je ne m'en suis pas encore servi donc n'hesites pas a
// changer/adapter/supprimer :) Il me semble qu'avant de partir en vacances
// tu m'avais montre une structure :)

// Eric: Pour pouvoir traiter les differentes variables de l'env il va falloir
// creer une struct cle/valeur car nous aurons pas gerer uniquement le "PATH="
// Principalement pour les built-in;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

// Pour traiter les $? il nous faudra mettre a jour constamment nos retours
// de fonction d'ou le last_status;

// # define BI_ECHO "echo"
// # define BI_CD "cd"
// # define BI_PWD "pwd"
// # define BI_EXPORT "export"
// # define BI_UNSET "unset"
// # define BI_ENV "env"
// # define BI_EXIT "exit"

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
}
t_builtin;

typedef struct s_msh
{
	t_env			*env;
	char			*history;
	bool			is_heredoc;
	bool			is_builtin;
	char			*builtin_names[NB_BUILTINS];
	int				(*builtin_funcs[NB_BUILTINS])(void);
}					t_msh;

int					launch_program(t_msh *msh);
void				print_banner(void);
void				struct_init(t_msh *msh);

// BUILT-IN
bool				is_builtin(t_msh *msh, char *s);
int					bi_exit(void);
int					bi_echo(void);
int					bi_cd(void);
int					bi_pwd(void);
int					bi_export(void);
int					bi_unset(void);
int					bi_env(void);
// SIGNALS
bool				is_eof(void);
void				is_sig_quit(int process);

#endif
