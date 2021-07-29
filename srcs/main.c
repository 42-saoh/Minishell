/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 22:00:23 by taesan            #+#    #+#             */
/*   Updated: 2021/07/29 12:50:34 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	start(t_info *info)
{
	if (info->pipe_cnt > 0)
	{
		printf("pipe 코드 타도록 !\n");
	}
	else
	{
		exec_command(info, 0, 0, 0);
	}
	return (0);
}

int main(int argc, char *argv[], char *envp[])
{
	char	*input;
	char	*filter_input;
	char	*prompt;
	t_info	info;

	// 설정의 PS1, PS2로 받아올 수 있도록. ?
	prompt = "$";
	// 종료 시그널 받으면 프로그램 끝내야 함.

	info.paths = set_path(envp);
	if (!info.paths)
		return (error_occur_std(SPLIT_ERR));
	info.envp = envp;
	while(1)
	{
		input = readline(prompt);
		if (ft_strcmp(input, "") == 0)
		{
			// free(input);
			continue;
		}
		add_history(input);
		filter_input = input_space_filter(input, ft_strlen(input) + 1);
		if (!filter_input)
			return (error_occur_std(MALLOC_ERR));
		init_info(&info, filter_input);
		start(&info);
		ft_free(input);
		ft_free(filter_input);
	}
	// clear heap
}