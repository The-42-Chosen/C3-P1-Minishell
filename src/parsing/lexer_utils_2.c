/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:53:57 by erpascua          #+#    #+#             */
/*   Updated: 2025/10/03 12:54:19 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_quotes(t_msh *msh, char *s, int *i)
{
	if (handle_quotes(s, i, s[*i]) == -1)
	{
		msh->exit_code = 2;
		return (-1);
	}
	if (s[*i] != 0 && !is_space(s[*i]))
		msh->is_append = true;
	return (0);
}
