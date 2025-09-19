/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:53:38 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/13 19:58:52 by gpollast         ###   ########.fr       */
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

char	*seek_group_redir(t_stack *stack)
{
	char	*res;

	if (stack->token == REDIR && stack->next
		&& stack->next->token == WORD)
	{
		res = ft_strdup(stack->next->content);
		if (!res)
		{
			g_exit_code = 12;
			return (NULL);
		}
		stack = stack->next;
		return (res);
	}
	g_exit_code = 2;
	if (!stack->next) // Cas newline
		ft_fprintf(2, "bash: syntax error near unexpected token `newline'\n");
	else if (stack->next->token != WORD)
		ft_fprintf(2, "bash: syntax error near unexpected token `%s'\n",
			stack->next->content);
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
	while (tmp && tmp->token == WORD)
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
	while (i < count && tmp)
	{
		group[i] = ft_strdup(tmp->content);
		if (!group[i])
		{
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
	while (i < (count - 1)) // FUITES MEMOIRES
	{
		i++;
		*stack = (*stack)->next;
	}
	group[count] = NULL;
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
	ft_memset(new_node, 0, sizeof(*new_node));
    return (new_node);
}

t_group	identify_redir(char *word)
{
	if (!ft_strncmp(word, "<", 1))
		return(G_REDIR_IN);
	else if (!ft_strncmp(word, ">", 1))
		return(G_REDIR_OUT);
	else if (!ft_strncmp(word, "<<", 2))
		return(G_REDIR_HEREDOC);
	else if (!ft_strncmp(word, ">>", 2))
		return(G_REDIR_APPEND);
	return (G_INVALID);
}

int	parse(t_msh *msh)
{
	t_stack	*tmp;
	t_data	*current_data;
	t_data	*new_node;

	tmp = msh->stack;
	current_data = NULL;
	while (tmp)
	{
		if (err_next_token(tmp, REDIR) || err_next_token(tmp, OPERATOR))
			return (0);
		if (tmp->token == REDIR)
		{
			new_node = init_data_node();
			if (!new_node)
				return (0);
			new_node->file_or_limiter = seek_group_redir(tmp);
			if (!new_node->file_or_limiter)
				return (0);
			new_node->group = identify_redir(tmp->content);
			ft_fprintf(1, "Expandable %d | REDIR %s\n", tmp->is_expandable, new_node->file_or_limiter);
			if (!msh->data)
				msh->data = new_node;
			else
				current_data->next = new_node;
			current_data = new_node;
			tmp = tmp->next;
		}
		else if (tmp->token == WORD)
		{
			new_node = init_data_node();
			if (!new_node)
				return (0);
			new_node->cmd = seek_group_cmd(&tmp);
			if (!new_node->cmd)
				return (0);
			new_node->group = G_CMD;
			print_array(new_node->cmd, "WORD");
			if (!msh->data)
				msh->data = new_node;
			else
				current_data->next = new_node;
			current_data = new_node;
		}
		else if (tmp->token == PIPE)
		{
			new_node = init_data_node();
			if (!new_node)
				return (0);
			new_node->group = G_PIPE;
			ft_fprintf(1, "PIPE |\n");
			if (!msh->data)
				msh->data = new_node;
			else
				current_data->next = new_node;
			current_data = new_node;
		}
		tmp = tmp->next;
	}
	return (1);
}
