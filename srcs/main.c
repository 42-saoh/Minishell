/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 22:00:23 by taesan            #+#    #+#             */
/*   Updated: 2021/07/30 17:27:50 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	command_string(t_info info)
{
	while (info.commands)
	{
		printf("[%s]\n", info.commands->content);
		info.commands = info.commands->next;
	}
}

int	start(t_info *info)
{
	/*
		init할 때, 파싱 제대로해서 2개이상의 명령어가 존재하는 경우.
		pipecnt말고, 명령어 갯수로 변경
	*/
	if (!init_info(info))
		return (0);
	return (0);
}

int main(int argc, char *argv[], char *envp[])
{
	char	*input;
	char	*prompt;
	t_info	info;

	// 설정의 PS1, PS2로 받아올 수 있도록. ?
	prompt = "$";
	// 종료 시그널 받으면 프로그램 끝내야 함.

	ft_memset(&info, 0, sizeof(t_info));
	info.paths = set_path(envp);
	if (!info.paths)
		return (error_occur_std(SPLIT_ERR));
	info.envp = envp;
	while(1)
	{
		input = readline(prompt);
		if (ft_strcmp(input, "") != 0)
		{
			add_history(input);
			if (!make_command_list(&info, input))
				break ;
			// command_string(info);
			if (start(&info))
			 	break ;
			ft_lstclear(&info.commands, ft_free);
		}
		ft_free(input);
	}
	// clear heap
}