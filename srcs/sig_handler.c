/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:45:29 by taesan            #+#    #+#             */
/*   Updated: 2021/09/01 17:19:35 by taekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrl_d_handler(void)
{
	ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
	ft_putstr_fd("\033[2C", STDOUT_FILENO);
	printf("exit\n");
	exit(0);
}

void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
