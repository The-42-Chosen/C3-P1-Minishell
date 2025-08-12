/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:02:25 by erpascua          #+#    #+#             */
/*   Updated: 2025/08/12 20:09:00 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	struct_init(t_msh *msh)
{
	msh->history = NULL;
	msh->last_status = 0;
	msh->is_builtin = 0;
	msh->is_heredoc = 0;
}
