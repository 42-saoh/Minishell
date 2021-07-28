/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 22:00:23 by taesan            #+#    #+#             */
/*   Updated: 2021/07/28 21:00:21 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	start(char *input, char *envp[])
{
	t_info	info;

	init_info(&info, input, envp);
	if (info.pipe_cnt > 0)
	{
		printf("pipe 코드 타도록 !\n");
	}
	else
	{
		printf("1개의 명령어를 수행 !\n");
	}

	return (0);
}

int main(int argc, char *argv[], char *envp[])
{
	char	*input;
	char	*filter_input;
	char	*prompt;

	// 설정의 PS1, PS2로 받아올 수 있도록.
	prompt = "$";

	// init()

	// 종료 시그널 받으면 프로그램 끝내야 함.
	while(1)
	{
		input = readline(prompt);
		add_history(input);
		filter_input = input_space_filter(input);
		if (!filter_input)
			return (error_occur_std(MALLOC_ERR));
		start(filter_input, envp);
		free(input);
		free(filter_input);
	}

	// free
}