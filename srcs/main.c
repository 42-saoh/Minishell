/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 22:00:23 by taesan            #+#    #+#             */
/*   Updated: 2021/08/14 01:06:54 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clear_data(t_info *info)
{
	if (info->commands)
		ft_lstclear(&info->commands, ft_free);
	if (info->redirect_lst)
		ft_lstclear(&info->redirect_lst, ft_free);
	// commands_symbol은 안해도 되는지?
}

void	error_occur_parsing(t_info *info, char *input)
{
	printf("%s\n", PARSE_ERR);
	clear_data(info);
	ft_free(input);
}

int	start(t_info *info)
{
	t_list *temp;
	int		seq;

	temp = info->commands;
	seq = 0;
	while (temp && info->command_cnt >= 0)
	{
		info->command_cnt--;
		if (!redirect_filter(info, (char **)(&temp->content)))
			return (0);
		if (!command_filter(info, (char **)(&temp->content)))
			return (0);
		if (!init_command_info(info, temp->content))
			return (0);
		if (info->command_cnt != 0 && !set_connect_pipe(info, seq))
		 	return (0);
		exec_call(info, seq++);
		// commands_symbol은 안해도 되는지?
		if (info->redirect_lst)
			ft_lstclear(&info->redirect_lst, ft_free);
		temp = temp->next;
	}
	return (1);
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
			if (make_command_list(&info, input) != 1)
			{
				error_occur_parsing(&info, input);
				continue ;
			}
			if (!start(&info))
			{
				error_occur_parsing(&info, input);
				continue ;
			}
			clear_data(&info);
		}
		ft_free(input);
	}
	// need clear pathes
}