/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 21:17:51 by taesan            #+#    #+#             */
/*   Updated: 2021/09/01 17:17:10 by taekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	remove_redirect(int s, int e, char **content)
{
	char	*left;
	char	*right;
	char	*new_input;

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

char	*get_right_str(char *content, int i)
{
	int	s;

	while (content[i] && content[i] == ' ')
		i++;
	if (content[i] == '&')
	{
		printf(UNEXPECTED_TOKEN);
		return (0);
	}
	s = i;
	while (content[i] && content[i] != ' ')
		i++;
	return (ft_substr(content + s, 0, i - s));
}

void	redirection_dup_exec(int fds[2])
{
	dup2(fds[1], fds[0]);
	ft_close(fds[1]);
}

int	get_ampersand_fd(char *content, int i)
{
	int	s;
	int	fd;

	i++;
	s = i;
	while (content[i] && ft_isdigit(content[i]))
		i++;
	fd = 0;
	while (s < i)
	{
		fd = (fd * 10) + (content[s] - '0');
		s++;
	}
	return (fd);
}
