/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_dup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 16:38:14 by taesan            #+#    #+#             */
/*   Updated: 2021/08/08 17:24:45 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	here_doc(t_redirect_in	*data_in, int fd_in)
{
	char	*buf;
	int		r;
	int		fd;

	fd = open(TEMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return (error_occur_perror(INPUT_OPEN_ERR));
	r = get_next_line(fd_in, &buf);
	while (r > 0)
	{
		if (ft_strcmp(buf, data_in->limiter) == 0)
			break ;
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		r = get_next_line(fd_in, &buf);
	}
	if (buf)
		free(buf);
	ft_close(fd);
	data_in->right_fd = open(TEMP_FILE, O_RDONLY);
	if (data_in->right_fd == -1)
		return (error_occur_perror(INPUT_OPEN_ERR));
	return (1);	
}

int	in_dup(t_info *info)
{
	t_list			*temp;
	t_redirect_in	*data_in;
	int				fd_in;

	fd_in = dup(STDIN_FILENO);
	temp = info->in;
	while (temp)
	{
		data_in = temp->content;
		if (data_in->limiter)
		{
			if (!here_doc(data_in, fd_in))
				break ;
		}
		dup2(data_in->right_fd, data_in->left_fd);
		ft_close(data_in->right_fd);
		temp = temp->next;
	}
	if (info->in)
		ft_lstclear(&info->in, redirect_in_free);
	ft_close(fd_in);
	return (1);	
}

void	out_dup(t_info *info)
{
	t_list			*temp;
	t_redirect_out	*data_out;

	temp = info->out;
	while (temp)
	{
		data_out = temp->content;
		dup2(data_out->right_fd, data_out->left_fd);
		ft_close(data_out->right_fd);
		temp = temp->next;
	}
	if (info->out)
		ft_lstclear(&info->out, redirect_out_free);
}

/*
	dup하면서 close해주는 코드 심기.
*/
int	redirection_dup(t_info *info)
{
	if (!in_dup(info))
		return (0);
	out_dup(info);
	return (1);
}