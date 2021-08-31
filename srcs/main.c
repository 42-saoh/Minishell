/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 22:00:23 by taesan            #+#    #+#             */
/*   Updated: 2021/08/30 14:25:46 by saoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_occur_parsing(t_info *info, char *input)
{
	printf("%s\n", PARSE_ERR);
	clear_data(info);
	ft_free(input);
}

/*
	command 수행 후, 다음 command로 이동한다.
	symbol을 확인하여, 다음 command를 pass한다.
*/
void	move_next_cmd(t_info *info, t_list **commands, t_list **symbols)
{
	int		symbol;
	int		pass;

	if (info->command_cnt == -1)
		return ;
	*commands = (*commands)->next;
	pass = 0;
	if (*commands)
	{
		if (*symbols)
		{
			symbol = *(int *)(*symbols)->content;
			if (symbol == DB_AMPER && info->exec_result != 0 || \
				symbol == DB_PIPE && info->exec_result == 0)
			{
				info->command_cnt--;
				*symbols = (*symbols)->next;
				move_next_cmd(info, commands, symbols);
			}
			else
				*symbols = (*symbols)->next;
		}
	}
}

void	start(t_info *info)
{
	t_list	*commands;
	t_list	*symbols;
	int		seq;

	commands = info->commands;
	symbols = info->commands_symbol;
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
		if (symbols && is_double_symbol(*(int *)symbols->content))
			exec_call(info, -1);
		else
			exec_call(info, seq++);
		move_next_cmd(info, &commands, &symbols);
	}
}

int	check_input(char *input)
{
	int	i;

	if (!input)
		ctrl_d_handler();
	i = 0;
	while (input[i] == ' ')
		i++;
	if (!input[i])
	{
		free(input);
		return (0);
	}
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*input;
	char	*prompt;
	t_info	info;

	prompt = "$";
	ft_memset(&info, 0, sizeof(t_info));
	if (!init_envp_and_signal(&info, envp))
		return (0);
	while (1)
	{
		input = readline(prompt);
		if (check_input(input))
		{
			add_history(input);
			if (make_command_list(&info, input) != 1)
			{
				error_occur_parsing(&info, input);
				continue ;
			}
			start(&info);
			clear_data(&info);
			ft_free(input);
		}
	}
	clear_all_data(&info);
}
