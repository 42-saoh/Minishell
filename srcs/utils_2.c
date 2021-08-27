/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 22:35:08 by taesan            #+#    #+#             */
/*   Updated: 2021/08/27 16:21:53 by taesan           ###   ########.fr       */
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
