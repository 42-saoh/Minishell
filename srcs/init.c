/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:49:55 by taesan            #+#    #+#             */
/*   Updated: 2021/07/30 19:02:23 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	따옴표 처리
*/
int	set_command_info(t_info *info, char *input)
{
	char	**input_sp;
	char	*cmd;
	char 	**temp;
	int		cmd_idx;

	input_sp = ft_split(input, ' ');
	if (!input_sp)
		return (error_occur_std(SPLIT_ERR));
	temp = ft_split(input_sp[0], '/');
	if (!temp)
		return (error_occur_std(SPLIT_ERR));
	cmd_idx = 0;
	while (temp[cmd_idx])
		cmd_idx++;
	info->is_builtin = check_builtin(temp[cmd_idx - 1]);
	split_free(temp);
	cmd = check_command(info->paths, input_sp[0], ft_strlen(input_sp[0]));
	if (cmd)
	{
		free(input_sp[0]);
		input_sp[0] = cmd;
	}
	info->param = input_sp;
	return (1);
}

int	init_info(t_info *info)
{
	// parsing을 먼저해야겠다, 파이프라인 존재하면 pipe사용해야 하니깐.

	// n개의 명령어를 찾아야 함.
	while (info->commands)
	{
		// printf("cmd : [%s]\n", info->commands->content);
		if (!command_filter(info))
			return (0);
		if (!set_command_info(info, info->commands->content))
			return (0);
		exec_command(info);
		info->commands = info->commands->next;
	}
	return (1);
}