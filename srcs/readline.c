/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 23:57:19 by taesan            #+#    #+#             */
/*   Updated: 2021/07/25 23:57:47 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wait_closing_quote(char start_q)
{
	char *temp;
	char last_char;

	while(1)
	{
		temp = readline(">");
		last_char = temp[ft_strlen(temp) - 1];
		add_history(temp);
		free(temp);
		if (last_char == start_q)
			break ;
	}
}