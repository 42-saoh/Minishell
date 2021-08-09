/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 14:45:56 by taesan            #+#    #+#             */
/*   Updated: 2021/08/08 17:06:57 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_process(t_info *info)
{
	char	*command;

	command = info->param[0];
	if (!redirection_dup(info))
		return ;
	execve(command, info->param, info->envp);
	perror("execve");
	exit(0);
}

void	parent_process(t_info *info)
{
	int	status;
	int	r;

	r = wait(&status);
	while (r == -1 && errno == EINTR)
		r = wait(&status);
	if (r == -1)
		perror(WAIT_ERR);
	split_free(info->param);
	info->param = 0;
}

void	exec_command(t_info *info)
{
	pid_t	cpid;

	if (info->is_builtin)
	{
		printf("is built in\n");
	}
	else
	{
		cpid = fork();
		if (cpid > 0)
			parent_process(info);
		else if (cpid < 0)
			perror("fork");
		else
			child_process(info);
	}
}