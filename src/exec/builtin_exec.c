/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:40:00 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/02 16:46:20 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin_process(t_msh *msh, t_process *process)
{
	int	cin;
	int	cout;

	cin = dup(0);
	cout = dup(1);
	ft_lstiter(process->inputs, (void (*)(void *))dup_all_read);
	ft_lstiter(process->outputs, (void (*)(void *))dup_all_write);
	execute_builtin(msh, process);
	dup2(cin, 0);
	dup2(cout, 1);
	close(cin);
	close(cout);
}