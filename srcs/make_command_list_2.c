/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_command_list_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekang <taekang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 16:41:12 by taekang           #+#    #+#             */
/*   Updated: 2021/09/06 16:41:13 by taekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*get_numpoint(int num)
{
	t_list	*data;
	int		*ptr;

	ptr = (int *)malloc(sizeof(int));
	if (!ptr)
		return (0);
	*ptr = num;
	data = ft_lstnew((void *)ptr);
	if (!data)
	{
		free(ptr);
		return (0);
	}
	return (data);
}

int	append_command(t_info *info, char *input, int s, int e)
{
	char	*temp;
	t_list	*data;

	temp = ft_substr(input + s, 0, e - s);
	if (!temp)
		return (error_occur_perror(MALLOC_ERR));
	if (is_empty(temp))
	{
		free(temp);
		return (0);
	}
	data = ft_lstnew(temp);
	if (!data)
	{
		free(temp);
		return (error_occur_perror(MALLOC_ERR));
	}
	ft_lstadd_back(&info->commands, data);
	info->command_cnt++;
	return (1);
}

int	append_pipe_command(t_info *info, char *input, int *s, int *e)
{
	t_list	*data;

	if (input[*e + 1] == PIPE)
	{
		if (!append_command(info, input, *s, *e))
			return (0);
		data = get_numpoint(DB_PIPE);
		if (!data)
			return (0);
		ft_lstadd_back(&info->commands_symbol, data);
		*s = *e + 2;
		*e = *e + 1;
	}
	else
	{
		if (!append_command(info, input, *s, *e))
			return (0);
		data = get_numpoint(SG_PIPE);
		if (!data)
			return (0);
		ft_lstadd_back(&info->commands_symbol, data);
		*s = *e + 1;
	}
	return (1);
}

int	append_amper_command(t_info *info, char *input, int *s, int *e)
{
	t_list	*data;

	if (input[*e + 1] == '&')
	{
		if (!append_command(info, input, *s, *e))
			return (0);
		data = get_numpoint(DB_AMPER);
		if (!data)
			return (0);
		ft_lstadd_back(&info->commands_symbol, data);
		*s = *e + 2;
		*e = *e + 1;
	}
	else
	{
		if (*e == 0)
			return (0);
		if (input[*e - 1] != '>' && input[*e - 1] != '<')
			return (0);
	}
	return (1);
}
