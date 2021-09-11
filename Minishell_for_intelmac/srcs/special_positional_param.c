/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_positional_param.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 16:10:46 by taesan            #+#    #+#             */
/*   Updated: 2021/09/06 16:39:28 by taekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*make_new_input_posi(char *input, int s, int *next_idx, char *value)
{
	char	*front;
	char	*back;
	char	*join;
	char	*result;

	result = 0;
	front = ft_substr(input, 0, s);
	if (!front)
		return (0);
	join = ft_strjoin(front, value);
	free(front);
	if (!join)
		return (0);
	*next_idx = ft_strlen(join) - 1;
	s += 2;
	back = ft_substr(input + s, 0, ft_strlen(input) - s);
	result = ft_strjoin(join, back);
	if (back)
		free(back);
	free(join);
	return (result);
}

char	*set_const_value(char c)
{
	if (c == '0')
		return (SHELL_NAME);
	if (c == '#')
		return ("0");
	return (0);
}

int	special_positional_param(t_info *info, char **ptr, int s, int *next_idx)
{
	char	*value;
	char	*result;
	int		need_free;

	need_free = 0;
	if ((*ptr)[s + 1] == '0' || (*ptr)[s + 1] == '#')
		value = set_const_value((*ptr)[s + 1]);
	else if ((*ptr)[s + 1] == '?')
	{
		value = ft_itoa(info->exec_result);
		need_free = 1;
	}
	else
		return (0);
	if (!value)
		return (-1);
	result = make_new_input_posi(*ptr, s, next_idx, value);
	if (!result)
		return (-1);
	free(*ptr);
	*ptr = result;
	if (need_free)
		ft_free(value);
	return (1);
}
