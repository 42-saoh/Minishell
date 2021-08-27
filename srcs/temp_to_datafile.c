/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_to_datafile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 05:20:53 by taesan            #+#    #+#             */
/*   Updated: 2021/08/27 05:20:54 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
	2에서 1으로 보냄
*/
int temp_to_datafile(char *read, char *write)
{
	int			fd;
	int			fd_2;
	char 		*line;
	struct stat	sb;

	fd_2 = open(read, O_RDONLY, S_IRWXU);
	if (fd_2 != -1)
	{
		stat(read, &sb);
		if (sb.st_size > 0)
		{
			fd = open(write, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
			while (get_next_line(fd_2, &line) > 0)
			{
				if (ft_strcmp("", line) != 0)
					ft_putendl_fd(line, fd);
			}
			if (ft_strcmp("", line) != 0)
				ft_putstr_fd(line, fd);
			ft_free(line);
			ft_close(fd);
			ft_close(fd_2);
		}
		if (unlink(read) == -1)
			error_occur_std(UNLINK_ERR);
	}
	return (1);
}