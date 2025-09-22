/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:50:26 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/22 14:29:29 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <minishell.h>

// void	create_pipes(t_pipe *pipefd, int nb_cmd)
// {
// 	int	i;

// 	i = 0;
// 	while (i < nb_cmd)
// 	{
// 		if (pipe(pipefd[i].fd) == -1)
// 			return (perror("pipe"));
// 		i++;
// 	}
// }

// int	process(t_msh *msh)
// {
// 	t_pipe		*pipefd;
// 	t_process	*process;

// 	pipefd = malloc(sizeof(t_pipe) * (msh->nb_cmd));
// 	if (!pipefd)
// 	{
// 		perror("Error allocating memory for pipes");
// 		exit(EXIT_FAILURE);
// 	}
// 	create_pipes(pipefd, msh->nb_cmd);
// 	process = setup_childs(msh->data);
// 	create_processes(process, pipefd, msh->data);
// 	close_pipes(pipefd, msh->nb_cmd);
// 	wait_children(process, msh->nb_cmd);
// 	cleanup_children(process, msh->nb_cmd);
// 	free(process);
// 	free(pipefd);
// }