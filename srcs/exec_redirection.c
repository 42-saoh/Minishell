/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:34:47 by taesan            #+#    #+#             */
/*   Updated: 2021/08/18 01:25:25 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_left_fd(char *content, int *i, int fd[2])
{
	fd[0] = 0;
	while (content[*i])
	{
		if (is_redirect(content[*i]))
		{
			if (content[*i] == REDIRECT_OUT && fd[0] == 0)
				fd[0] = 1;
			if (fd[0] > FD_MAX)
			{
				printf("%d: %s\n", fd[0], BAD_FD);
				return (0);
			}
			return (1);
		}
		if (!ft_isdigit(content[*i]))
			break ;
		fd[0] = fd[0] * 10 + content[*i] - '0';
		*i += 1;
	}
	return (error_occur_std(PARSE_ERR)); 
}

int	exec_redirection(t_info *info)
{
	t_list	*temp;
	char	*content;
	int		i;

	temp = info->redirect_lst;
	while (temp)
	{
		content = (char *)temp->content;
		i = 0;
		if (!set_left_fd(content, &i, info->redirect_fd))
			return (0);
		if (content[i] == REDIRECT_IN && \
			!(redirect_in_dup(info, info->std_in, content + i + 1)))
			return (0);
		else if (content[i] == REDIRECT_OUT && \
			!(redirect_out_dup(info->redirect_fd, content + i + 1)))
			return (0);
		//printf("left : [%d] , right : [%d]\n", info->redirect_fd[0], info->redirect_fd[1]);
		temp = temp->next;
	}
	return (1);
}
