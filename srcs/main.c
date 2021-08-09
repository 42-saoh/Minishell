/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 22:00:23 by taesan            #+#    #+#             */
/*   Updated: 2021/08/09 16:14:15 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clear_data(t_info *info)
{
	if (info->commands)
		ft_lstclear(&info->commands, ft_free);
	if (info->in)
		ft_lstclear(&info->in, redirect_in_free);
	if (info->out)
		ft_lstclear(&info->out, redirect_out_free);
}

void	start(t_info *info)
{
	t_list *temp;

	temp = info->commands;
	printf("cnt : [%d]\n", info->command_cnt);
	while (temp && info->command_cnt >= 0)
	{
		if (!command_filter(info, (char **)(&temp->content)))
			return ;
		// redirect처리
		if (!redirect_filter(info, (char **)(&temp->content)))
			return ;
		// printf("===== ===== after ===== =====\n");
		// redirect_in_to_string(*info);
		// redirect_out_to_string(*info);
		if (!init_command_info(info, temp->content))
			return ;
		if (info->command_cnt > 1 && !info->in && !info->out)
		{
			// 파이프가 존재하면서,

			// 해당 명령어에 
			// pipe code 
		}
		else
			exec_command(info);
		info->command_cnt--;
		temp = temp->next;
	}
}

int main(int argc, char *argv[], char *envp[])
{
	int		r;
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
			r = make_command_list(&info, input);
			if (!r)
				break ;
			if (r == 1)
				start(&info);
			clear_data(&info);
		}
		ft_free(input);
	}
	// need clear pathes
}