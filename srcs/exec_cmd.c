// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   exec_command.c                                     :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2021/06/28 14:45:56 by taesan            #+#    #+#             */
// /*   Updated: 2021/07/05 20:21:26 by taesan           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../pipex.h"

// int	exec_dup2(t_pipe *info, int pipe[2], int flags, int is_last)
// {
// 	if ((flags & STDIN_PIPE) && dup2(pipe[READ_FD_IDX], STDIN_FILENO) < 0)
// 		return (error_occur_perror(DUP2_ERR));
// 	if (flags & STDOUT_PIPE)
// 	{
// 		if (is_last)
// 		{
// 			if (dup2(info->result_fd, STDOUT_FILENO) < 0)
// 				return (error_occur_perror(DUP2_ERR));
// 			close(info->result_fd);
// 		}
// 		else if (dup2(pipe[WRITE_FD_IDX], STDOUT_FILENO) < 0)
// 			return (error_occur_perror(DUP2_ERR));
// 	}
// 	return (1);
// }

// void	child_process(t_pipe *info, int pipe[2], int flags, int is_last)
// {
// 	int		dup_r;
// 	char	*command;

// 	dup_r = exec_dup2(info, pipe, flags, is_last);
// 	close(pipe[0]);
// 	close(pipe[1]);
// 	if (dup_r)
// 	{
// 		command = info->param[0];
// 		execve(command, info->param, info->envp);
// 		perror("execve");
// 		exit(0);
// 	}
// }

// void	parent_process(t_pipe *info, int pipe[2], int flags, int is_last)
// {
// 	int	status;

// 	if (wait(&status) == -1)
// 		perror(WAIT_ERR);
// 	split_free(info->param);
// 	info->param = 0;
// 	if (flags & STDIN_PIPE)
// 		close(pipe[READ_FD_IDX]);
// 	if (flags & STDOUT_PIPE)
// 	{
// 		if (is_last)
// 			close(info->result_fd);
// 		else
// 			close(pipe[WRITE_FD_IDX]);
// 	}
// }

// void	exec_command(t_pipe *info, int pipe[2], int flags, int is_last)
// {
// 	pid_t	cpid;

// 	cpid = fork();
// 	if (cpid > 0)
// 		parent_process(info, pipe, flags, is_last);
// 	else if (cpid < 0)
// 		perror("fork");
// 	else
// 		child_process(info, pipe, flags, is_last);
// }

// int	exec_call(t_pipe *info, const char *param, char **paths, int is_last)
// {
// 	if (!set_param_info(info, param, paths))
// 		return (0);
// 	if (!is_last)
// 		exec_command(info, info->connect_pipe, STDIN_PIPE | STDOUT_PIPE, 0);
// 	else
// 		exec_command(info, info->pipe_out, STDIN_PIPE | STDOUT_PIPE, 1);
// 	return (1);
// }
