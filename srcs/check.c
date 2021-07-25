/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 23:50:42 by taesan            #+#    #+#             */
/*   Updated: 2021/07/25 23:55:20 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (ECHO);
	if (ft_strcmp(cmd, "cd") == 0)
		return (CD);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (PWD);
	if (ft_strcmp(cmd, "export") == 0)
		return (EXPORT);
	if (ft_strcmp(cmd, "unset") == 0)
		return (UNSET);
	if (ft_strcmp(cmd, "env") == 0)
		return (ENV);
	if (ft_strcmp(cmd, "exit") == 0)
		return (EXIT);
	return (NOT_BUILTIN);
}

/*
	pipe 존재하는지
	큰 따옴표나 작은 따옴표 존재하는지 && 홀 수 인경우 에러
	큰 따옴표, 작은 따옴표 동시에 존재하면, 먼저 어떤걸로 적용할지.
*/
int		check_input(char *input, t_info *info)
{
	info->single_q = 0;
	info->double_q = 0;
	info->pipe_cnt = 0;
	info->start_q = 0;
	while (*input)
	{
		if (*input == SINGLE_Q)
			info->single_q++;
		else if (*input == DOUBLE_Q)
			info->double_q++;
		else if (*input == PIPE)
			info->pipe_cnt++;
		if (info->single_q == 1 && info->double_q == 0)
			info->start_q = SINGLE_Q;
		else if (info->single_q == 0 && info->double_q == 1)
			info->start_q = DOUBLE_Q;
		input += 1;
	}
	if (info->single_q % 2 != 0 || info->double_q % 2 != 0)
		wait_closing_quote(info->start_q);
	return (1);
}