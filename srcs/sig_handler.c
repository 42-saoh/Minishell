/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:45:29 by taesan            #+#    #+#             */
/*   Updated: 2021/09/03 20:05:33 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrl_d_handler(t_info *info)
{
	ft_putstr_fd("\033[1A", STDOUT_FILENO);
	ft_putstr_fd("\033[2C", STDOUT_FILENO);
	printf("exit\n");
	clear_all_data(info);
	exit(0);
}

void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\033[%dC  \n", rl_end + 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sigint_occur(t_info *info)
{
	info->exec_result = 130;
	printf("\b\b");
}
