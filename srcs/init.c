/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:49:55 by taesan            #+#    #+#             */
/*   Updated: 2021/07/28 20:56:47 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_command_info(t_info *info, char *input)
{
	char	**input_sp;
	char	*cmd;

	// 따옴표가 있는경우 따로처리 ??

	input_sp = ft_split(input, ' ');
	if (!input_sp)
		return (error_occur_std(SPLIT_ERR));
	cmd = check_command(info->paths, input_sp[0], ft_strlen(input_sp[0]));
	if (cmd)
	{
		free(input_sp[0]);
		input_sp[0] = cmd;
	}
	info->param = input_sp;
	return (1);
}

/*
	pipe 존재하는지
	큰 따옴표나 작은 따옴표 존재하는지 && 홀 수 인경우 에러
	큰 따옴표, 작은 따옴표 동시에 존재하면, 먼저 어떤걸로 적용할지.
*/
void	set_input_info(t_info *info, char *input)
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
	/*
		이 경우, 문자열로 인식하도록 해야 함
	*/
	if ((info->start_q = SINGLE_Q && info->single_q % 2 != 0) || \
		(info->start_q = DOUBLE_Q && info->double_q % 2 != 0))
	{
		
	}	
}

int	init_info(t_info *info, char *input, char *envp[])
{
	info->paths = set_path(envp);
	if (!info->paths)
		return (error_occur_std(SPLIT_ERR));
	info->envp = envp;
	set_input_info(info, input);
	set_command_info(info, input);
	

	return (1);
}