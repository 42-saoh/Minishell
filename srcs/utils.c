/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 22:35:08 by taesan            #+#    #+#             */
/*   Updated: 2021/07/29 21:38:53 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		manage_chars(char c)
{
	if (c == SINGLE_Q || c == DOUBLE_Q || c == PIPE)
		return (1);
	return (0);
}

void	jump_space(char **input)
{
	char *str;

	if (!input)
		return ;
	str = *input;
	while (str && *str == ' ')
	{
		*input += 1;
		str = *input;
	}
}

char	*get_str(char **input)
{
	char	*org;
	char	*temp;
	char	*str;
	int		i;

	jump_space(input);
	org = *input;
	temp = *input;
	i = 0;
	while (*temp && *temp != ' ')
	{
		*input += 1;
		temp = *input;
		i++;
	}
	str = ft_substr(org, 0, i);
	if (!str)
		error_occur_std(SPLIT_ERR);
	return (str);
}