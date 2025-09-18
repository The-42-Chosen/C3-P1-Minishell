/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:53:38 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/18 14:50:12 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_next_token_for_redir(t_stack *stack, t_token t)
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
	if (!stack->next)
		ft_fprintf(2, "bash: syntax error near unexpected token `newline'\n");
	else if (stack->next->token != WORD)
		ft_fprintf(2, "bash: syntax error near unexpected token `%s'\n",
			stack->next->content);
	return (NULL);
}

int	count_nb_cmd(t_stack **stack)
{
	int		nb_cmd;
	t_stack	*tmp;

	nb_cmd = 0;
	tmp = *stack;
	while (tmp && tmp->token == WORD)
	{
		nb_cmd++;
		tmp = tmp->next;
	}
	return (nb_cmd);
}

char	**setup_cmd(t_stack *stack, int nb_cmd)
{
	char	**group;
	t_stack	*tmp;
	int		i;

	group = calloc((nb_cmd + 1), sizeof(char *));
	if (!group)
		return (g_exit_code = 12, NULL);
	tmp = stack;
	i = 0;
	while (i < nb_cmd && tmp)
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
	return (group);
}

char	**seek_group_cmd(t_stack **stack)
{
	int		nb_cmd;
	char	**group;
	int		i;

	nb_cmd = count_nb_cmd(stack);
	group = setup_cmd(*stack, nb_cmd);
	if (!group)
		return (NULL);
	i = 0;
	while (i < nb_cmd - 1)
	{
		*stack = (*stack)->next;
		i++;
	}
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
	int	len;

	len = ft_strlen(word);
	if (!ft_strncmp(word, "<", len))
		return (G_REDIR_IN);
	else if (!ft_strncmp(word, ">", len))
		return (G_REDIR_OUT);
	else if (!ft_strncmp(word, "<<", len))
		return (G_REDIR_HEREDOC);
	else if (!ft_strncmp(word, ">>", len))
		return (G_REDIR_APPEND);
	return (G_INVALID);
}

int	set_up_path(t_msh *msh)
{
	t_data	*tmp;

	tmp = msh->data;
	while (tmp)
	{
		if (tmp->group == G_CMD)
		{
			tmp->cmd.path = cmd_path(msh, tmp->cmd.args[0]);
			ft_fprintf(1, "Path cmd: %s\n", tmp->cmd.path);
		}
		tmp = tmp->next;
	}
	return (1);
}

t_data	*data_last(t_data *data)
{
	while (data)
	{
		if (data->next != 0)
			data = data->next;
		if (data->next == 0)
			return (data);
	}
	return (NULL);
}

t_data	*data_add_back(t_data *data, t_data *new)
{
	if (!data || !new)
		return (NULL);
	if (data == NULL)
	{
		data = new;
		return (NULL);
	}
	else
		data_last(data)->next = new;
	return (data);
}

int	add_redir_node(t_stack **tmp, t_data *new_node)
{
	new_node->file_or_limiter = seek_group_redir(*tmp);
	if (!new_node->file_or_limiter)
		return (0);
	new_node->group = identify_redir((*tmp)->content);
	ft_fprintf(1, "%d | REDIR %s\n", new_node->group,
		new_node->file_or_limiter);
	(*tmp) = (*tmp)->next;
	return (1);
}

int	add_command_node(t_stack **tmp, t_data *new_node)
{
	new_node->cmd.args = seek_group_cmd(tmp);
	if (!new_node->cmd.args)
		return (0);
	new_node->group = G_CMD;
	print_array(new_node->cmd.args, "WORD");
	return (1);
}

int	add_node(t_msh *msh, t_stack **tmp)
{
	t_data	*new_node;

	new_node = init_data_node();
	if (!new_node)
		return (0);
	if ((*tmp)->token == REDIR)
	{
		if (!add_redir_node(tmp, new_node))
			return (0);
	}
	else if ((*tmp)->token == WORD)
	{
		if (!add_command_node(tmp, new_node))
			return (0);
	}
	else if ((*tmp)->token == PIPE)
	{
		new_node->group = G_PIPE;
		ft_fprintf(1, "PIPE |\n");
	}
	msh->data = data_add_back((msh->data), new_node);
	return (1);
}

int	parse(t_msh *msh)
{
	t_stack	*tmp;

	tmp = msh->stack;
	while (tmp)
	{
		if (check_next_token_for_redir(tmp, REDIR))
			return (0);
		if (!add_node(msh, &tmp))
			return (0);
		tmp = tmp->next;
	}
	set_up_path(msh);
	return (1);
}
