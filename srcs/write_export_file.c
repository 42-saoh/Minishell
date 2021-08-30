/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_export_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 03:57:34 by taesan            #+#    #+#             */
/*   Updated: 2021/08/27 05:22:33 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exist_env(char *var)
{
	int		env_fd;
	char	*line;
	int		exist;

	env_fd = open(ENV_FILE, O_RDONLY);
	if (env_fd == -1)
		return (0);
	exist = 0;
	while (get_next_line(env_fd, &line) > 0)
	{
		if (env_file_cmp(line, var) == 0)
		{
			exist = 1;
			break ;
		}
	}
	if (!exist && env_file_cmp(line, var) == 0)
		exist = 1;
	ft_free(line);
	ft_close(env_fd);
	return (exist);
}

int	write_export_file(char *param)
{
	if (exist_env(param))
		return (1);
	if (!datafile_to_temp(EXPORT_FILE, EXPORT_FILE_2, param, param))
		return (0);
	if (!temp_to_datafile(EXPORT_FILE_2, EXPORT_FILE))
		return (0);
	return (1);
}
