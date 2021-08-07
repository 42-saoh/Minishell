/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 14:45:56 by taesan            #+#    #+#             */
/*   Updated: 2021/08/08 02:16:06 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirection_change(t_info *info)
{
	t_list	*temp;
	t_redirect_in 	*data_in;
	t_redirect_out	*data_out;

	temp = info->in;
	while (temp)
	{
		data_in = temp->content;
		dup2(data_in->right_fd, data_in->left_fd);
		temp = temp->next;
	}
	temp = info->out;
	while (temp)
	{
		data_out = temp->content;
		dup2(data_out->right_fd, data_out->left_fd);
		temp = temp->next;
	}
}

void	child_process(t_info *info)
{
	int		dup_r;
	char	*command;

	command = info->param[0];
	redirection_change(info);
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