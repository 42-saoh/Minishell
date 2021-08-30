/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 22:35:08 by taesan            #+#    #+#             */
/*   Updated: 2021/08/30 14:26:47 by saoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_double_symbol(int symbol)
{
	if (symbol == DB_AMPER || symbol == DB_PIPE)
		return (1);
	return (0);
}

void	jump_space(char *input, int *i)
{
	// 1. 앞에있는 스페이스 뛰어넘기.
	while (input[*i] && input[*i] == ' ')
		*i += 1;
}

void	clear_pipe(t_info *info, int pipe[2], int flags)
{
	if (!pipe)
		pipe = info->pipe_out;
	if (flags & STDIN_PIPE)
		close(pipe[READ_FD_IDX]);
	if (flags & STDOUT_PIPE)
		close(pipe[WRITE_FD_IDX]);
}

void	builtin_set(t_info *info, int pipe[2])
{
	int	result;

	if (!pipe && info->is_builtin == EXIT && info->exec_result != EXEC_FAIL)
	{
		result = info->exec_result;
		ft_free(info->input);
		clear_all_data(info);
		exit(result);
	}
	else if (!pipe && info->is_builtin == EXIT &&
			info->exec_result == EXEC_FAIL)
		info->command_cnt = -1;
	else if (info->is_builtin == CD && info->exec_result == 0)
		builtin_cd_parent(info);
	else if (info->is_builtin == EXPORT || info->is_builtin == UNSET)
		copy_envp(info);
}
