/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 00:23:10 by taesan            #+#    #+#             */
/*   Updated: 2021/08/27 00:55:06 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_export(t_info *info)
{
	int		i;
	char	**temp;
	t_list	*list;

	if (!info->param[1])
	{
		list = 0;
		if (export_file_merge(info, &list))
		{
			temp = (char **)malloc(sizeof(char *) * (info->envp_cnt + 1));
			if (!temp)
				exit (EXEC_FAIL);
			merge_sort(info->envp, temp, 0, info->envp_cnt - 1);
			ft_free(temp);
			print_export(info);
			ft_lstclear(&list, ft_free);
		}
	}
	else
		export_add_var(info);
	exit(0);
}
