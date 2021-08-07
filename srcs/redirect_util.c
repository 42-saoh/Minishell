/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 21:17:51 by taesan            #+#    #+#             */
/*   Updated: 2021/08/08 01:14:34 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		remove_redirect(int s, int e, char **content)
{
	char *left;
	char *right;
	char *new_input;

	new_input = 0;
	left = ft_substr(*content, 0, s);
	if (left)
	{
		right = ft_substr(*content + e, 0, ft_strlen(*content) - e);
		if (right)
		{
			new_input = ft_strjoin(left, right);
			ft_free(right);
		}
		ft_free(left);
	}
	if (!new_input)
		return (0);
	ft_free(*content);
	*content = new_input;
	return (1);
}


int		get_fd(int s, int e, char *content)
{
	int fd;

	fd = 0;
	while (s < e)
	{
		fd = (fd * 10) + (content[s] - '0'); 
		s++;
	}
	return (fd);
}

char	*get_right_str(char *content, int *e)
{
	int		i;
	int		s;

	i = *e + 1;
	while (content[i] && content[i] == ' ')
		i++;
	s = i;
	// 단순히 스페이스로 넘겨도 되는지.. 예외 문자가 있을라나..
	while (content[i] && content[i] != ' ')
		i++;
	*e = i;
	return (ft_substr(content + s, 0, i - s));
}