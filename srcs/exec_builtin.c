/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 14:54:24 by taesan            #+#    #+#             */
/*   Updated: 2021/08/19 15:54:01 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//◦ export with no options
// ◦ unset with no options
//◦ env with no options or arguments

#include "../includes/minishell.h"

/*
	$해석하도록 해야 함.
*/
int		ft_export(t_info *info)
{
	printf("ft_export.. size : %d\n", info->envp_cnt);
}

int		ft_unset(t_info *info)
{
	printf("ft_unset\n");
	return (0);
}

int		ft_env(t_info *info)
{
	char **envp;

	envp = info->envp;
	while (*envp)
	{
		ft_putendl_fd(*envp, 1);
		envp++;
	}
	return (0);
}

void	exec_builtin(int cmd, t_info *info)
{
	int r;

	if (cmd == EXPORT)
		r = ft_export(info);
	else if (cmd == UNSET)
		r = ft_unset(info);
	else if (cmd == ENV)
		r = ft_env(info);
	if (!r)
		exit(EXEC_FAIL);
	exit(0);
}