/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:45:29 by taesan            #+#    #+#             */
/*   Updated: 2021/08/27 13:33:43 by saoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrl_d_handler(void)
{
	printf("exit\n");
	exit(0);
}

void	sigint_handler(int signo)
{
	printf("push SIGINT\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
