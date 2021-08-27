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

// /*
// 	export -> export2로 복사
// */
// int export_to_export2(char *var, int remove)
// {
// 	int fd;
// 	int visited;
// 	int fd_2;
// 	char *line;

// 	line = 0;
// 	fd = open(EXPORT_FILE, O_RDONLY, S_IRWXU); // export는 없을 수 있음.
// 	if (fd != -1)
// 	{
// 		fd_2 = open(EXPORT_FILE_2, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
// 		if (fd_2 == -1)
// 			return (error_occur_std(FILE_OPEN_ERR));
// 		visited = 0;
// 		while (get_next_line(fd, &line) > 0)
// 		{
// 			if (!visited && ft_strcmp(var, line) == 0)
// 			{
// 				visited = 1;
// 				if (!remove)
// 					ft_putendl_fd(var, fd_2);
// 			}
// 			else
// 				ft_putendl_fd(line, fd_2);
// 		}
// 		// 1. 마지막 read가 중복인지 체크.
// 		// 마지막 문자가 중복인지 체크한다. 중복이면 바꿔주면 끝이다. 
// 		// fd < 0은 export파일이 없을 때, 그냥 export2에 현재 내용을 써준다.
// 		if (!visited && (ft_strcmp(line, var) == 0))
// 		{
// 			if (!remove)
// 				ft_putstr_fd(var, fd_2);
// 		}
// 		else
// 		{
// 			// 중복이면서, remove인 경우가 존재할 수 있다.
// 			// 중복이 아니면, 마지막 놈을 쓴 다음에, visited를 안했을 때만 key, value값을 추가한다.
// 			ft_putstr_fd(line, fd_2);
// 			if (!visited && !remove)
// 			{
// 				// 이거는 새로 변수를 추가하는거고
// 				ft_putchar_fd('\n', fd_2);
// 				ft_putstr_fd(var, fd_2);
// 			}
// 		}
// 		ft_free(line);
// 		ft_close(fd);
// 		ft_close(fd_2);
// 		if (fd > 0 && unlink(EXPORT_FILE) == -1)
// 			error_occur_std(UNLINK_ERR);
// 	}
// 	return (1);
// }

int		exist_env(char *var)
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

int write_export_file(char *param)
{
	// env파일에 존재하면 추가하지 않음.
	if (exist_env(param))
		return (1);
	if (!datafile_to_temp(EXPORT_FILE, EXPORT_FILE_2, param, param))
		return (0);
	if (!temp_to_datafile(EXPORT_FILE_2, EXPORT_FILE))
		return (0);
	return (1);
}