/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 14:45:56 by taesan            #+#    #+#             */
/*   Updated: 2021/07/29 12:23:35 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_process(t_info *info, int pipe[2], int flags, int is_last)
{
	int		dup_r;
	char	*command;

	command = info->param[0];
	execve(command, info->param, info->envp);
	perror("execve");
	exit(0);
}

void	parent_process(t_info *info, int pipe[2], int flags, int is_last)
{
	int	status;

	if (wait(&status) == -1)
		perror(WAIT_ERR);
	split_free(info->param);
	info->param = 0;
}

void	exec_command(t_info *info, int pipe[2], int flags, int is_last)
{
	pid_t	cpid;

	cpid = fork();
	if (cpid > 0)
		parent_process(info, pipe, flags, is_last);
	else if (cpid < 0)
		perror("fork");
	else
		child_process(info, pipe, flags, is_last);
}