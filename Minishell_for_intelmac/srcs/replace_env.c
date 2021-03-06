/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekang <taekang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 16:39:04 by taekang           #+#    #+#             */
/*   Updated: 2021/09/06 16:39:37 by taekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_dollar_value(char **envp, char *input)
{
	int	i;
	int	exist;

	while (*envp)
	{
		i = 0;
		exist = 1;
		while (pass_possible(input[i]))
		{
			if (!(*envp)[i] || (*envp)[i] != input[i])
			{
				exist = 0;
				break ;
			}
			i++;
		}
		if (exist && (*envp)[i] != '=')
			exist = 0;
		if (exist)
			return (*envp + i + 1);
		envp++;
	}
	return ("");
}

char	*make_new_input(char *input, int s, int *next_idx, char *value)
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
	*next_idx = ft_strlen(join);
	s++;
	while (pass_possible_2(input[s], next_idx))
		s++;
	back = ft_substr(input + s, 0, ft_strlen(input) - s);
	result = ft_strjoin(join, back);
	if (back)
		free(back);
	free(join);
	return (result);
}

int	replace_env(t_info *info, char **ptr, int s, int *next_idx)
{
	char	*value;
	char	*result;
	int		is_positional;

	is_positional = special_positional_param(info, ptr, s, next_idx);
	if (is_positional == -1)
		return (0);
	if (!is_positional)
	{
		value = get_dollar_value(info->envp, *ptr + s + 1);
		result = make_new_input(*ptr, s, next_idx, value);
		if (!result)
			return (error_occur_perror(MAKE_NEW_INPUT_ERR));
		free(*ptr);
		*ptr = result;
	}
	return (1);
}
