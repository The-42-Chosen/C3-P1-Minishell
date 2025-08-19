/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:02:25 by erpascua          #+#    #+#             */
/*   Updated: 2025/08/19 19:14:53 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	link_builtins(t_msh *msh)
{
	msh->builtin_names[BI_ECHO] = "echo";
	msh->builtin_funcs[BI_ECHO] = &bi_echo;
	msh->builtin_names[BI_CD] = "cd";
	msh->builtin_funcs[BI_CD] = &bi_cd;
	msh->builtin_names[BI_ENV] = "env";
	msh->builtin_funcs[BI_ENV] = &bi_env;
	msh->builtin_names[BI_PWD] = "pwd";
	msh->builtin_funcs[BI_PWD] = &bi_pwd;
	msh->builtin_names[BI_EXIT] = "exit";
	msh->builtin_funcs[BI_EXIT] = &bi_exit;
	msh->builtin_names[BI_EXPORT] = "export";
	msh->builtin_funcs[BI_EXPORT] = &bi_export;
	msh->builtin_names[BI_UNSET] = "unset";
	msh->builtin_funcs[BI_UNSET] = &bi_unset;
}

void	struct_init(t_msh *msh)
{
	msh->entry = NULL;
	msh->env = NULL;
	msh->history = NULL;
	msh->is_builtin = 0;
	msh->is_heredoc = 0;
	link_builtins(msh);
}
