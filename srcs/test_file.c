/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 00:06:30 by taesan            #+#    #+#             */
/*   Updated: 2021/08/14 00:18:01 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	command_to_string(t_info info)
{
	t_list *temp;

    temp = info.commands;
	while (temp)
	{
		printf("[%s]\n", (char *)temp->content);
		temp = temp->next;
	}
}