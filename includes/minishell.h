/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:31:03 by erpascua          #+#    #+#             */
/*   Updated: 2025/08/11 11:01:43 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>

// DEV: Eric: J'ai creer une premiere structure qui reprend le path de pipex et qui nous permettra de faire quelques tests.
// Au moment je redige ceci je ne m'en suis pas encore servi donc n'hesites pas changer/adapter/supprimer :)
// Il me semble qu'avant de partir en vacances tu m'avais montre une structure :)

typedef struct s_msh
{
	char	**env;
	char	*path;
	bool	is_heredoc;
	bool	is_builtin;
}			t_msh;

#endif
