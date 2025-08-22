/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:31:03 by erpascua          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/08/12 14:31:08 by erpascua         ###   ########.fr       */
=======
/*   Updated: 2025/08/11 19:40:47 by erpascua         ###   ########.fr       */
>>>>>>> df10aac ((feat) Minishell program launch setup on progress)
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
<<<<<<< HEAD
# include <term.h>
=======
>>>>>>> df10aac ((feat) Minishell program launch setup on progress)

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

typedef struct s_msh
{
	t_env			*env;
	char			*entry;
	char			*history;
	bool			is_heredoc;
	bool			is_builtin;
	char			*builtin_names[NB_BUILTINS];
	int				(*builtin_funcs[NB_BUILTINS])(void);
}					t_msh;

int					launch_program(void);
<<<<<<< HEAD
void				print_banner(void);
=======
>>>>>>> df10aac ((feat) Minishell program launch setup on progress)

#endif
