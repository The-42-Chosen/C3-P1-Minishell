/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:50:26 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/22 20:14:28 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <sys/wait.h>

static pid_t	execute_cmd(t_msh *msh, t_data *data, int in)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(0, in);
		execve(data->cmd.path, data->cmd.args, msh_getenv(msh));
	}
	return (pid);
}

t_list	*execute(t_msh *msh, t_data *data, int in)
{
	t_list	*item;

	item = malloc(sizeof(*item));
	if (!item)
		return (NULL);
	item->content = malloc(sizeof(pid_t));
	if (data->group == G_CMD)
	{
		if (data->cmd.builtin_type == BI_NONE)
			*((pid_t *)item->content) = execute_cmd(msh, data, in);
		else
			execute_builtin(msh, msh->data);
	}
	// execute(msh, data->next, in);
	return (item);
}

void	execute_all(t_msh *msh)
{
	t_list	*pids;
	
	pids = execute(msh, msh->data, 0);
	while (pids)
	{
		waitpid(*((pid_t *)(pids->content)), &msh->exit_code, 0);
		pids = pids->next;
	}
}
