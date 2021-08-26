/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 05:30:38 by taesan            #+#    #+#             */
/*   Updated: 2021/08/27 05:51:11 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	read_and_remove(t_data_to_temp *info, int(*cmp_func)(const char *, const char *))
{
	int visited;
	char *line;

	line = 0;
	visited = 0;
	while (get_next_line(info->read_fd, &line) > 0)
	{
		if (!visited && cmp_func(line, info->key) == 0)
			visited = 1;
		else
			ft_putendl_fd(line, info->write_fd);
		ft_free(line);
	}
	if (cmp_func(line, info->key) != 0)
		ft_putstr_fd(line, info->write_fd);
	ft_free(line);
	ft_close(info->read_fd);
	ft_close(info->write_fd);
}

// // env_file2 -> env_file1로 복사
// if (!temp_to_datafile(ENV_FILE_2, ENV_FILE))
// 	exit(EXEC_FAIL);
int remove_var(char *r_file, char *w_file, char *key)
{
	t_data_to_temp info;

	info.read_fd = open(r_file, O_RDONLY, S_IRWXU);
	if (info.read_fd == -1)
		return (1);
	info.write_fd = open(w_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	if (info.write_fd == -1)
	{
		ft_close(info.read_fd);
		return (error_occur_std(FILE_OPEN_ERR));
	}
	info.key = key;
	if (ft_strcmp(r_file, ENV_FILE) == 0)
		read_and_remove(&info, env_file_cmp);
	else
		read_and_remove(&info, ft_strcmp);
	if (unlink(r_file) == -1)
		error_occur_std(UNLINK_ERR);
	return (temp_to_datafile(w_file, r_file));
}