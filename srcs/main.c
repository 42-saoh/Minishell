/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 22:00:23 by taesan            #+#    #+#             */
/*   Updated: 2021/08/03 20:26:00 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	command_string(t_info info)
{
	t_list *temp;
	
	while (info.commands)
	{
		printf("[%s]\n", info.commands->content);
		info.commands = info.commands->next;
	}
}

void	start(t_info *info)
{
	t_list *temp;

	temp = info->commands;
	printf("cnt : [%d]\n", info->command_cnt);
	while (temp)
	{
		if (!command_filter(info, (char **)(&temp->content)))
			return ;
		// redirect처리
		if (!redirect_filter(info, (char **)(&temp->content)))
			return ;
		if (!init_command_info(info, temp->content))
			return ;
		if (info->command_cnt > 1)
		{
			printf("is pipe code\n");
			// pipe code 
		}
		else
			exec_command(info);
		temp = temp->next;
	}
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
	info.paths = init_path(envp);
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
			start(&info);
			ft_lstclear(&info.commands, ft_free);
		}
		ft_free(input);
	}
	// need clear pathes
}