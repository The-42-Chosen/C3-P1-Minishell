/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ep <ep@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:02:25 by erpascua          #+#    #+#             */
/*   Updated: 2025/09/19 15:25:32 by ep               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	link_builtins(t_msh *msh)
{
	msh->builtin_names[BI_ECHO] = ft_strdup("echo");
	msh->builtin_funcs[BI_ECHO] = &bi_echo;
	msh->builtin_names[BI_CD] = ft_strdup("cd");
	msh->builtin_funcs[BI_CD] = &bi_cd;
	msh->builtin_names[BI_ENV] = ft_strdup("env");
	msh->builtin_funcs[BI_ENV] = &bi_env;
	msh->builtin_names[BI_PWD] = ft_strdup("pwd");
	msh->builtin_funcs[BI_PWD] = &bi_pwd;
	msh->builtin_names[BI_EXIT] = ft_strdup("exit");
	msh->builtin_funcs[BI_EXIT] = &bi_exit;
	msh->builtin_names[BI_EXPORT] = ft_strdup("export");
	msh->builtin_funcs[BI_EXPORT] = &bi_export;
	msh->builtin_names[BI_UNSET] = ft_strdup("unset");
	msh->builtin_funcs[BI_UNSET] = &bi_unset;
}

int	struct_init(t_msh *msh)
{
	ft_memset(msh, 0, sizeof(*msh));
	link_builtins(msh);
	return (1);
}
