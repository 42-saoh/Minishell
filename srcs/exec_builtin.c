/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 14:54:24 by taesan            #+#    #+#             */
/*   Updated: 2021/08/31 20:05:52 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_builtin(int cmd, t_info *info)
{
	if (cmd == EXPORT)
		builtin_export(info);
	else if (cmd == UNSET)
		builtin_unset(info);
	else if (cmd == ENV)
		builtin_env(info);
	else if (cmd == CD)
		builtin_cd_sib(info);
	else if (cmd == PWD)
		builtin_pwd(info);
	else if (cmd == EXIT)
		builtin_exit(info);
	else if (cmd == ECHO)
		builtin_echo(info);
	exit(0);
}
