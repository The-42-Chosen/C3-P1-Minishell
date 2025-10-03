/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:02:25 by erpascua          #+#    #+#             */
/*   Updated: 2025/10/03 14:31:25 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	link_builtins(t_msh *msh)
{
	msh->builtin_names[BI_ECHO] = ft_strdup("echo");
	if (!msh->builtin_names[BI_ECHO])
		return (msh->exit_code = 12, 0);
	msh->builtin_funcs[BI_ECHO] = &bi_echo;
	if (!msh->builtin_funcs[BI_ECHO])
		return (0);
	msh->builtin_names[BI_CD] = ft_strdup("cd");
	if (!msh->builtin_names[BI_CD])
		return (msh->exit_code = 12, 0);
	msh->builtin_funcs[BI_CD] = &bi_cd;
	if (!msh->builtin_funcs[BI_CD])
		return (0);
	msh->builtin_names[BI_PWD] = ft_strdup("pwd");
	if (!msh->builtin_names[BI_PWD])
		return (msh->exit_code = 12, 0);
	msh->builtin_funcs[BI_PWD] = &bi_pwd;
	if (!msh->builtin_funcs[BI_PWD])
		return (0);
	msh->builtin_names[BI_EXPORT] = ft_strdup("export");
	if (!msh->builtin_names[BI_EXPORT])
		return (msh->exit_code = 12, 0);
	msh->builtin_funcs[BI_EXPORT] = &bi_export;
	if (!msh->builtin_funcs[BI_EXPORT])
		return (0);
	msh->builtin_names[BI_UNSET] = ft_strdup("unset");
	if (!msh->builtin_names[BI_UNSET])
		return (msh->exit_code = 12, 0);
	msh->builtin_funcs[BI_UNSET] = &bi_unset;
	if (!msh->builtin_funcs[BI_UNSET])
		return (0);
	msh->builtin_names[BI_ENV] = ft_strdup("env");
	if (!msh->builtin_names[BI_ENV])
		return (msh->exit_code = 12, 0);
	msh->builtin_funcs[BI_ENV] = &bi_env;
	if (!msh->builtin_funcs[BI_ENV])
		return (0);
	msh->builtin_names[BI_EXIT] = ft_strdup("exit");
	if (!msh->builtin_names[BI_EXIT])
		return (msh->exit_code = 12, 0);
	msh->builtin_funcs[BI_EXIT] = &bi_exit;
	if (!msh->builtin_funcs[BI_EXIT])
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
