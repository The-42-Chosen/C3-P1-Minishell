/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:31:03 by erpascua          #+#    #+#             */
/*   Updated: 2025/08/11 19:40:47 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>

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

typedef struct s_msh
{
	t_env			*env;
	int				last_status;
	bool			is_heredoc;
	bool			is_builtin;
}					t_msh;

int					launch_program(void);

#endif
