/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 22:35:08 by taesan            #+#    #+#             */
/*   Updated: 2021/08/01 20:04:46 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_quotation(char c)
{
	if (c == SINGLE_Q || c == DOUBLE_Q)
		return (1);
	return (0);
}

int		pass_possible(char c)
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