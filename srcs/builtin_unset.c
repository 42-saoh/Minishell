/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 00:23:58 by taesan            #+#    #+#             */
/*   Updated: 2021/08/27 05:47:41 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_unset(t_info *info)
{
	int	i;

	i = 1;
	while (info->param[i])
	{
		if (!remove_var(ENV_FILE, ENV_FILE_2, info->param[i]))
			exit(EXEC_FAIL);
		if (!remove_var(EXPORT_FILE, EXPORT_FILE_2, info->param[i]))
			exit(EXEC_FAIL);
		i++;
	}
	exit(0);
}
