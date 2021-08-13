/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:45:29 by taesan            #+#    #+#             */
/*   Updated: 2021/08/12 13:19:40 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	ctrl + \
*/
void	sigquit_handler(int signo)
{
	rl_redisplay();
	return ;
}
/*
	ctrl + c
*/
void	sigint_handler(int signo)
{
	// rl_replace_line("\n$", 0);
	write(1, "\n$", 3);
	return ;
}
/*
	ctrl + d ..
	signal 없음
*/
void	ctrl_d_handler(int signo)
{
	rl_redisplay();
	return ;
}