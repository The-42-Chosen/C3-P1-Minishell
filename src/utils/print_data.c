/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:23:44 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/25 17:14:32 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_data(t_msh *msh)
{
	t_data	*tmp2;

	tmp2 = msh->data;
	while (tmp2)
	{
		if (tmp2->group == G_REDIR_IN)
			ft_fprintf(1, "REDIR_IN\n");
		if (tmp2->group == G_REDIR_OUT)
			ft_fprintf(1, "REDIR_OUT\n");
		if (tmp2->group == G_REDIR_APPEND)
			ft_fprintf(1, "REDIR_APPEND\n");
		if (tmp2->group == G_REDIR_HEREDOC)
			ft_fprintf(1, "REDIR_HEREDOC\n");
		if (tmp2->group == G_PIPE)
			ft_fprintf(1, "PIPE\n");
		if (tmp2->group == G_CMD)
		{
			if (tmp2->cmd.builtin_type == BI_NONE)
				ft_fprintf(1, "PATH: %s ", tmp2->cmd.path);
			ft_fprintf(1, "CMD: ");
			print_string_array(tmp2->cmd.args);
		}
		tmp2 = tmp2->next;
	}
}
