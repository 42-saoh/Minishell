/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 22:00:23 by taesan            #+#    #+#             */
/*   Updated: 2021/07/28 20:04:23 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_cmd(char *input, char *envp[])
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
	char *input;
	char *prompt;

	// 설정의 PS1, PS2로 받아올 수 있도록.
	prompt = "$";

	// init()

	// 종료 시그널 받으면 프로그램 끝내야 함.
	while(1)
	{
		input = readline(prompt);
		exec_cmd(input, envp);
		add_history(input);
		free(input);
	}

	// free
}