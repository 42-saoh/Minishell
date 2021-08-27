/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:53:36 by taesan            #+#    #+#             */
/*   Updated: 2021/08/26 22:58:00 by taesan           ###   ########.fr       */
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

char	*list_to_string(t_list *list)
{
	t_list	*temp;
	char	*str;
	int		len;
	int		i;
	int		j;

	temp = list;
	len = 0;
	while (temp)
	{
		len += ft_strlen((char *)temp->content);
		temp = temp->next;
	}
	str = (char *)malloc(sizeof(char *) * (len + 1));
	if (str)
	{
		str[len] = 0;
		i = 0;
		temp = list;
		while (temp)
		{
			j = 0;
			while (((char *)(temp->content))[j])
				str[i++] = ((char *)(temp->content))[j++];
			temp = temp->next;
		}
	}
	return (str);
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
	t_strjoin	temp;

	ft_bzero(&temp, sizeof(t_strjoin));
	data = 0;
	if (info->temp_list)
	{
		temp.front = list_to_string(info->temp_list);
		ft_lstclear(&info->temp_list, ft_free);
		temp.back_s = *s;
		temp.back_len = *i - *s;
		data = front_back_join(input, &temp);
	}
	else
	{
		if (*i != *s)
		{
			temp.content = ft_substr(input + *s, 0, *i - *s);
			if (temp.content)
				data = ft_lstnew(temp.content);
		}
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

int last(t_info *info, char *input, int i, int s)
{
	t_list *temp;

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
/*
	실패하면 list2개를 비워줘야한다.
	temp_list
	param_list
*/
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