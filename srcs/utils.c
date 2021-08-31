/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 22:35:08 by taesan            #+#    #+#             */
/*   Updated: 2021/08/08 17:23:48 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_empty(char *temp)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		if (temp[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	is_quotation(char c)
{
	if (c == SINGLE_Q || c == DOUBLE_Q)
		return (1);
	return (0);
}

int	pass_possible(char c)
{
	if (!c)
		return (0);
	if (is_quotation(c))
		return (0);
	if (c == '|')
		return (0);
	if (c == ' ')
		return (0);
	return (1);
}

int	is_redirect(char c)
{
	if (c == REDIRECT_IN || c == REDIRECT_OUT)
		return (1);
	return (0);
}

void	ft_close(int fd)
{
	if (fd <= 2)
		return ;
	close(fd);
}
