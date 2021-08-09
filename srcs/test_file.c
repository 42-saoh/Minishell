/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 00:06:30 by taesan            #+#    #+#             */
/*   Updated: 2021/08/08 01:25:33 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	command_to_string(t_info info)
{
	t_list *temp;

    temp = info.commands;
	while (temp)
	{
		printf("[%s]\n", temp->content);
		temp = temp->next;
	}
}

void	redirect_in_to_string(t_info info)
{
	t_list *temp;
	
	printf("[ redirect_in_to_string ]\n");
	
    temp = info.in;
	while (temp)
	{
        t_redirect_in *data = temp->content;
		printf("left : [%d], right : [%d], limiter : [%s]\n", data->left_fd, data->right_fd, data->limiter);
		temp = temp->next;
	}
}

void	redirect_out_to_string(t_info info)
{
	t_list *temp;

	printf("[ redirect_out_to_string ]\n");
	
    temp = info.out;
	while (temp)
	{
        t_redirect_out *data = temp->content;
		printf("left : [%d], right : [%d], is_append : [%d]\n", data->left_fd, data->right_fd, data->is_append);
		temp = temp->next;
	}
}