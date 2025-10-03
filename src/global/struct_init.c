/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:02:25 by erpascua          #+#    #+#             */
/*   Updated: 2025/10/03 15:38:23 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_builtin(t_msh *msh, int index, const char *name,
		int (*func)(t_msh *, t_process *process, char **))
{
	msh->builtin_names[index] = ft_strdup(name);
	if (!msh->builtin_names[index])
		return (msh->exit_code = 12, 0);
	msh->builtin_funcs[index] = func;
	if (!msh->builtin_funcs[index])
		return (0);
	return (1);
}

static int	link_builtins(t_msh *msh)
{
	if (!set_builtin(msh, BI_ECHO, "echo", &bi_echo))
		return (0);
	if (!set_builtin(msh, BI_CD, "cd", &bi_cd))
		return (0);
	if (!set_builtin(msh, BI_PWD, "pwd", &bi_pwd))
		return (0);
	if (!set_builtin(msh, BI_EXPORT, "export", &bi_export))
		return (0);
	if (!set_builtin(msh, BI_UNSET, "unset", &bi_unset))
		return (0);
	if (!set_builtin(msh, BI_ENV, "env", &bi_env))
		return (0);
	if (!set_builtin(msh, BI_EXIT, "exit", &bi_exit))
		return (0);
	return (1);
}

int	struct_init(t_msh *msh)
{
	ft_memset(msh, 0, sizeof(*msh));
	if (!link_builtins(msh))
		return (0);
	return (1);
}
