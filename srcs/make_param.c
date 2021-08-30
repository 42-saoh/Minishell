/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:53:36 by taesan            #+#    #+#             */
/*   Updated: 2021/08/30 20:16:01 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*front_back_join(char *input, t_strjoin *temp)
{
	t_list	*data;

	data = 0;
	if (!temp->front)
		temp->front = ft_substr(input + temp->front_s, 0, temp->front_len);
	if (temp->front)
	{
		temp->back = ft_substr(input + temp->back_s, 0, temp->back_len);
		if (temp->back)
		{
			temp->content = ft_strjoin(temp->front, temp->back);
			ft_free(temp->back);
			if (temp->content)
				data = ft_lstnew(temp->content);
		}
		ft_free(temp->front);
	}
	return (data);
}

int	append_temp_list(t_info *info, char *input, int *i, int *s)
{
	t_strjoin	temp;
	t_list		*data;
	char		c;

	ft_bzero(&temp, sizeof(t_strjoin));
	c = input[*i];
	temp.front_s = *s;
	temp.front_len = *i - *s;
	*i += 1;
	*s = *i;
	while (input[*i] && input[*i] != c)
		*i += 1;
	temp.back_s = *s;
	temp.back_len = *i - *s;
	*s = *i + 1;
	data = front_back_join(input, &temp);
	if (!data)
		return (0);
	ft_lstadd_back(&info->temp_list, data);
	return (1);
}

int	append_param_list(t_info *info, char *input, int *i, int *s)
{
	t_list		*data;
	char		*content;

	content = 0;
	data = 0;
	if (info->temp_list)
		data = list_to_string(info, input, i, s);
	if (!info->temp_list && *i != *s)
	{
		content = ft_substr(input + *s, 0, *i - *s);
		if (content)
			data = ft_lstnew(content);
	}
	if (*i != *s && !data)
		return (0);
	if (data)
	{
		ft_lstadd_back(&info->param_list, data);
		info->param_cnt++;
		jump_space(input, i);
		*s = *i;
	}
	return (1);
}

int	last(t_info *info, char *input, int i, int s)
{
	t_list	*temp;

	if (!append_param_list(info, input, &i, &s))
		return (0);
	info->param = (char **)malloc(sizeof(char *) * (info->param_cnt + 1));
	if (!info->param)
		return (0);
	info->param[info->param_cnt] = 0;
	i = 0;
	temp = info->param_list;
	while (temp && i < info->param_cnt)
	{
		info->param[i++] = (char *)temp->content;
		temp = temp->next;
	}
	return (1);
}

int	make_param(t_info *info, char *input, int len)
{
	int		i;
	int		s;

	i = 0;
	jump_space(input, &i);
	s = i;
	while (i < len && input[i])
	{
		if (i < len && is_quotation(input[i]))
		{
			if (!append_temp_list(info, input, &i, &s))
				return (0);
		}
		else if (i < len && input[i] == ' ')
		{
			if (!append_param_list(info, input, &i, &s))
				return (0);
			i--;
		}
		i++;
	}
	return (last(info, input, i, s));
}
