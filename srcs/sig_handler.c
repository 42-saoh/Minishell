/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:45:29 by taesan            #+#    #+#             */
/*   Updated: 2021/08/26 14:25:16 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

typedef struct	s_test
{
	void	(*test)(int);
}				t_test;

void	ctrl_d_handler(void)
{
	printf("exit\n");
	exit(0);
}

void	sigint_handler(int signo)
{
	printf("push SIGINT\n");
	rl_on_new_line();
	//rl_replace_line("",0);
	//rl_redisplay();
}

// int main()
// {
// 	char *str;
// 	t_test test;
// 	t_test test1;

// 	test.test = signal(SIGINT, sigint_handler);
// 	test1.test = signal(SIGQUIT, SIG_IGN);
// 	while(1)
// 	{
// 		str = readline("test : ");
// 		add_history(str);
// 		if (!str)
// 			ctrl_d_handler();
// 		free(str);
// 		str = 0;
// 	}
// }
