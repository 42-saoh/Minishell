/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datafile_to_temp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 03:45:01 by taesan            #+#    #+#             */
/*   Updated: 2021/08/27 05:29:24 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	ft_strcmp랑 동일한 방식으로 return 되도록 해야 함.
	같은 경우 0 return 되도록
*/
int		env_file_cmp(const char *line, const char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (!line[i] || key[i] != line[i])
			return (1);
		i++;
	}
	if (!line[i] || line[i] != '=')
		return (1);
	return (0);
}

void	last_line(t_data_to_temp *info, int visited, char *line)
{
	if (line)
		ft_putstr_fd(line, info->write_fd);
	if (!visited)
	{
		if (line)
			ft_putchar_fd('\n', info->write_fd);
		ft_putstr_fd(info->param, info->write_fd);
	}
}

void	read_and_write(t_data_to_temp *info, int(*cmp_func)(const char *, const char *))
{
	int		visited;
	char	*line;
		
	visited = 0;
	line = 0;
	while (info->read_fd > 0 && get_next_line(info->read_fd, &line) > 0)
	{
		if (!is_empty(line))
		{
			if (!visited && cmp_func(line, info->key) == 0)
			{
				visited = 1;
				ft_putendl_fd(info->param, info->write_fd);
			}
			else
				ft_putendl_fd(line, info->write_fd);
		}
		ft_free(line);
	}
	if (!visited && (info->read_fd > 0 && cmp_func(line, info->key) == 0))
		ft_putstr_fd(info->param, info->write_fd);
	else
		last_line(info, visited, line);
	ft_free(line);
	ft_close(info->write_fd);
}

int		datafile_to_temp(char *r_file, char *w_file, char *key, char *param)
{
	t_data_to_temp	info;
	int				is_env;

	is_env = 0;
	if (ft_strcmp(r_file, ENV_FILE) == 0)
		is_env = 1;
	ft_bzero(&info, sizeof(t_data_to_temp));
	info.read_fd = open(r_file, O_RDONLY, S_IRWXU);
	if (is_env && info.read_fd == -1)
		return (1);
	info.write_fd = open(w_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	if (info.write_fd == -1)
	{
		ft_close(info.read_fd);
		return (error_occur_std(FILE_OPEN_ERR));
	}
	info.key = key;
	info.param = param;
	if (is_env)
		read_and_write(&info, env_file_cmp);
	else
		read_and_write(&info, ft_strcmp);
	ft_close(info.read_fd);
	if (info.read_fd > 0 && unlink(r_file) == -1)
		error_occur_std(UNLINK_ERR);
	return (1);
}