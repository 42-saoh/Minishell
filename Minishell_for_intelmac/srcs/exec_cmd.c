/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 14:45:56 by taesan            #+#    #+#             */
/*   Updated: 2021/09/02 19:08:34 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_dup2(int pipe[2], int flags)
{
	if ((flags & STDIN_PIPE) && dup2(pipe[READ_FD_IDX], STDIN_FILENO) < 0)
		return (error_occur_perror(DUP2_ERR));
	if ((flags & STDOUT_PIPE) && dup2(pipe[WRITE_FD_IDX], STDOUT_FILENO) < 0)
		return (error_occur_perror(DUP2_ERR));
	if (flags & STDIN_PIPE)
		close(pipe[READ_FD_IDX]);
	if (flags & STDOUT_PIPE)
		close(pipe[WRITE_FD_IDX]);
	return (1);
}

void	child_process(t_info *info, int pipe[2], int flags)
{
	int		dup_r;
	char	*command;

	dup_r = 1;
	if (pipe)
		dup_r = exec_dup2(pipe, flags);
	if (!redirection_dup(info))
		exit(1);
	if (dup_r)
	{
		command = info->param[0];
		if (info->is_builtin)
			exec_builtin(info->is_builtin, info);
		else
		{
			execve(command, info->param, info->envp);
			stderr_print(SHELL_NAME, command, COMMAND_NOT_FOUND);
			exit(127);
		}
	}
	exit(0);
}

void	parent_process(t_info *info, int pipe[2], int flags)
{
	int			status;
	int			r;
	struct stat	sb;

	r = wait(&status);
	while (r == -1 && errno == EINTR)
		r = wait(&status);
	if (r == -1)
		error_occur_perror(WAIT_ERR);
	info->exec_result = exit_status(status);
	if (term_status(status) == SIGINT)
		sigint_occur(info);
	clear_pipe(info, pipe, flags);
	if (info->is_builtin)
		builtin_set(info, pipe);
	split_free(info->param);
	info->param_cnt = 0;
	info->asterisk_check = 0;
	if (info->redirect_lst)
		ft_lstclear(&info->redirect_lst, ft_free);
	if (stat(TEMP_FILE, &sb) == 0 && unlink(TEMP_FILE) == -1)
		error_occur_perror(UNLINK_ERR);
}

void	exec_command(t_info *info, int pipe[2], int flags)
{
	pid_t	cpid;

	cpid = fork();
	if (cpid > 0)
		parent_process(info, pipe, flags);
	else if (cpid < 0)
		error_occur_perror("fork");
	else
		child_process(info, pipe, flags);
}

void	exec_call(t_info *info, int seq)
{
	if ((info->command_cnt == 0 && seq == 0) || seq == -1)
		exec_command(info, 0, STDIN_PIPE | STDOUT_PIPE);
	else if (info->command_cnt > 0 && seq == 0)
		exec_command(info, info->connect_pipe, STDOUT_PIPE);
	else if (info->command_cnt == 0 && seq > 0)
		exec_command(info, info->pipe_out, STDIN_PIPE);
	else
		exec_command(info, info->connect_pipe, STDIN_PIPE | STDOUT_PIPE);
}
