/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 00:21:46 by taesan            #+#    #+#             */
/*   Updated: 2021/08/27 00:27:00 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_env(t_info *info)
{
	char **envp;

	envp = info->envp;
	while (*envp)
	{
		if (!is_empty(*envp))
			ft_putendl_fd(*envp, STDOUT_FILENO);
		envp++;
	}
	exit(0);
}