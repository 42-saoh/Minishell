/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 22:00:23 by taesan            #+#    #+#             */
/*   Updated: 2021/08/18 03:13:44 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clear_data(t_info *info)
{
	if (info->commands)
		ft_lstclear(&info->commands, ft_free);
	if (info->redirect_lst)
		ft_lstclear(&info->redirect_lst, ft_free);
	if (info->commands_symbol)
		ft_lstclear(&info->commands_symbol, ft_free);
	ft_close(info->std_in);
}

void	error_occur_parsing(t_info *info, char *input)
{
	printf("%s\n", PARSE_ERR);
	clear_data(info);
	ft_free(input);
}

int	check_finish(t_info *info)
{
	int symbol;

	if (info->commands_symbol)
	{
		symbol = *(int *)info->commands_symbol->content;
		if ((symbol == DB_PIPE || symbol == DB_AMPER) && info->exec_result == EXEC_FAIL)
			return (1) ;
		info->commands_symbol = info->commands_symbol->next;
	}
	return (0);
}

void	start(t_info *info)
{
	t_list	*commands;
	int		seq;

	commands = info->commands;
	seq = 0;
	while (commands && info->command_cnt >= 0)
	{
		info->command_cnt--;
		if (!redirect_filter(info, (char **)(&commands->content)))
			return ;
		if (!command_filter(info, (char **)(&commands->content)))
			return ;
		if (!init_command_info(info, commands->content))
			return ;
		if (info->command_cnt != 0 && !set_connect_pipe(info, seq))
		 	return ;
		exec_call(info, seq++);
		if (check_finish(info))
			return ;
		commands = commands->next;
	}
}

int	check_input(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ')
		i++;
	if (!input[i])
		return (0);
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
		if (input && check_input(input))
		{
			add_history(input);
			if (make_command_list(&info, input) != 1)
			{
				error_occur_parsing(&info, input);
				continue ;
			}
			start(&info);
			clear_data(&info);
		}
		ft_free(input);
	}
	// need clear pathes
}
