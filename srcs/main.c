/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 22:00:23 by taesan            #+#    #+#             */
/*   Updated: 2021/07/26 15:41:38 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_cmd(int cmd, char *input, char *envp[], t_instruction *inst)
{
	printf("cmd : [%s]\n", inst->cmd);
	return (0);
}

int	parse_instruction(char *input, char *envp[])
{
	t_instruction	inst;
	t_info	info;
	char	*str;
	int		i;

	check_input(input, &info);
	while (*input)
	{
		str = get_str(&input);
		if (!str)
			return (0);
		if (i == 0)
		{
			inst.cmd = str;
			if (!inst.cmd)
				return (0);
			exec_cmd(check_builtin(inst.cmd), input, envp, &inst);
		}
		i++;
		//printf("str : [%s]\n", str);
	}
	return (1);
}

/*
	need: [ \ , ; , ' , ", | ] 처리
*/
int	start(char *input, char *envp[])
{
	int		i;
	char	**paths;

	// 파라미터 파싱.
	parse_instruction(input, envp);

	// 경로 받아오고,
	paths = set_path(envp);
	if (!paths)
		return (0);
	i = 0;

	// 1. 입력 명령어가 존재하는지 먼저 확인.
	// 2. 존재하면, 
		// 파라미터 확인 후 execve
	// 3. 존재하지 않으면, 
		// path와 연결해서 확인
		// 파라미터 확인
		// execve

	return (1);
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
		start(input, envp);

		// 1. 명령어 parsing

		// 2. 명령어에 해당하는,  실행프로그램 존재 하는지. (pipex 참조)

		// 명령어는 history에 저장, 커서로 왔다갔다 하도록
		add_history(input);
		//printf("%s\n", input);
		free(input);
	}

	// free
}