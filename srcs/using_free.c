/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   using_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:56:59 by taesan            #+#    #+#             */
/*   Updated: 2021/07/28 19:57:08 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	split_free(char **data)
{
	int	i;

	if (!data || !*data)
		return ;
	i = 0;
	while (data[i])
	{
		if (data[i])
		{
			free(data[i]);
			data[i] = 0;
		}
		i++;
	}
	free(data);
	data = 0;
}