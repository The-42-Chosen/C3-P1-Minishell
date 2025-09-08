/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:53:38 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/08 14:12:34 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	err_next_token(t_stack *stack, t_token t)
{
	if (stack->token == t)
	{
		if (stack->next && stack->next->token == t)
		{
			g_exit_code = 2;
			ft_fprintf(2, "bash: syntax error near unexpected token `%s'\n",
				stack->next->content);
			return (1);
		}
	}
	return (0);
}

char	**seek_group_redir(t_stack **stack)
{
	char	**group;

	if ((*stack)->token == REDIR && (*stack)->next
		&& (*stack)->next->token == WORD)
	{
		group = malloc(3 * sizeof(char *));
		if (!group)
		{
			g_exit_code = 12;
			return (NULL);
		}
		group[0] = (*stack)->content;
		group[1] = (*stack)->next->content;
		group[2] = NULL;
		(*stack) = (*stack)->next;
		return (group);
	}
	g_exit_code = 2;
	if (!(*stack)->next) // Cas newline
		ft_fprintf(2, "bash: syntax error near unexpected token `newline'\n");
	else if ((*stack)->next->token != WORD)
		ft_fprintf(2, "bash: syntax error near unexpected token `%s'\n",
			(*stack)->next->content);
	return (NULL);
}

char	**seek_group_cmd(t_stack **stack)
{
	int		count;
	char	**group;
	t_stack	*tmp;
	int		i;

	count = 0;
	tmp = *stack;
	while (tmp && tmp->token == WORD) // Vérifier tmp != NULL
	{
		count++;
		tmp = tmp->next;
	}
	group = malloc((count + 1) * sizeof(char *));
	if (!group)
	{
		g_exit_code = 12;
		return (NULL);
	}
	i = 0;
	tmp = *stack;
	while (i < count && tmp) // Vérifier tmp != NULL
	{
		group[i] = ft_strdup(tmp->content);
		if (!group[i]) // Vérifier ft_strdup
		{
			// Libérer la mémoire déjà allouée
			while (--i >= 0)
				free(group[i]);
			free(group);
			g_exit_code = 12;
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	i = 0;
	while (i < (count - 1))
	{
		i++;
		(*stack) = (*stack)->next;
	}
	group[count] = NULL; // Terminer le tableau
	return (group);
}

void	print_array(char **array, char *type)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		ft_fprintf(1, "%s %d %s\n", type, i, array[i]);
		i++;
	}
}

t_data	*init_data_node(void)
{
    t_data	*new_node;

    new_node = malloc(sizeof(t_data));
    if (!new_node)
    {
        g_exit_code = 12;
        return (NULL);
    }
    new_node->cmd = NULL;
    new_node->redir = NULL;
    new_node->operator = NULL;
    new_node->group = 0;
    new_node->next = NULL;
    return (new_node);
}

int	parse(t_msh *msh)
{
	t_stack	*tmp;

	tmp = msh->stack;
	while (tmp)
	{
		if (err_next_token(tmp, REDIR) || err_next_token(tmp, OPERATOR))
			return (0);
		if (tmp->token == REDIR)
		{
			msh->data = init_data_node();
			if (!msh->data)
				return (0);
			msh->data->redir = seek_group_redir(&tmp);
			if (!msh->data->redir)
				return (0);
			msh->data->group = G_REDIR;
			print_array(msh->data->redir, "REDIR");
			msh->data = msh->data->next;
		}
		else if (tmp->token == WORD)
		{
			msh->data = init_data_node();
			if (!msh->data)
				return (0);
			msh->data->cmd = seek_group_cmd(&tmp);
			if (!msh->data->cmd)
				return (0);
			msh->data->group = G_CMD;
			print_array(msh->data->cmd, "WORD");
			msh->data = msh->data->next;
		}
		else if (tmp->token == PIPE)
		{
			msh->data = init_data_node();
			if (!msh->data)
				return (0);
			msh->data->group = G_PIPE;
			ft_fprintf(1, "PIPE |\n");
			msh->data = msh->data->next;
		}
		else
		{
			msh->data = init_data_node();
			if (!msh->data)
				return (0);
			msh->data->group = G_OPERATOR;
			ft_fprintf(1, "PIPE |\n");
			msh->data = msh->data->next;
		}
		tmp = tmp->next;
	}
	return (1);
}
