/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 19:30:47 by taesan            #+#    #+#             */
/*   Updated: 2021/08/30 20:15:32 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_list_str_len(t_list *list)
{
	t_list	*temp;
	int		len;

	temp = list;
	len = 0;
	while (temp)
	{
		len += ft_strlen((char *)temp->content);
		temp = temp->next;
	}
	return (len);
}

char	*get_list_to_str(t_list *list)
{
	t_list	*temp;
	char	*str;
	int		len;
	int		i;
	int		j;

	len = get_list_str_len(list);
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

t_list	*list_to_string(t_info *info, char *input, int *i, int *s)
{
	t_list		*data;
	t_strjoin	temp;

	ft_bzero(&temp, sizeof(t_strjoin));
	data = 0;
	if (info->temp_list)
	{
		temp.front = get_list_to_str(info->temp_list);
		ft_lstclear(&info->temp_list, ft_free);
		temp.back_s = *s;
		temp.back_len = *i - *s;
		data = front_back_join(input, &temp);
	}
	return (data);
}
