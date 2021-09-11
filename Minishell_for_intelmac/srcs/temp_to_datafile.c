/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_to_datafile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 05:20:53 by taesan            #+#    #+#             */
/*   Updated: 2021/08/31 20:22:02 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	write_line(char *line, int fd)
{
	if (ft_strcmp("", line) != 0)
		ft_putendl_fd(line, fd);
	ft_free(line);
}

int	temp_to_datafile(char *read, char *write)
{
	int			fd;
	int			fd_2;
	char		*line;
	struct stat	sb;

	fd_2 = open(read, O_RDONLY, S_IRWXU);
	if (fd_2 != -1)
	{
		stat(read, &sb);
		if (sb.st_size > 0)
		{
			fd = open(write, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
			while (get_next_line(fd_2, &line) > 0)
				write_line(line, fd);
			write_line(line, fd);
			ft_close(fd);
			ft_close(fd_2);
		}
		if (unlink(read) == -1)
			error_occur_perror(UNLINK_ERR);
	}
	return (1);
}
