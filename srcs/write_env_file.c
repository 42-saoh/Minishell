/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_env_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 03:57:34 by taesan            #+#    #+#             */
/*   Updated: 2021/08/26 04:29:01 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_duplicate(char *line, char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (!line[i] || key[i] != line[i])
			return (0);
		i++;
	}
	if (!line[i] || line[i] != '=')
		return (0);
	return (1);
}

void	write_new_line(int fd, char *key, char *value)
{
	ft_putstr_fd(key, fd);
	write(fd, "=", 1);
	ft_putstr_fd(value, fd);
}

/*
	env_file읽어서 env_file2로 복사한다.
	중간에 중복값있으면 변경해 줌.
*/
int	evnp_to_envp2(char *key, char *value)
{
	int		fd;
	int		visited;
	int		fd_2;
	char	*line;

	fd = open(ENV_FILE, O_RDONLY, S_IRWXU); // -1이여도 return (1)되고있음.
	if (fd != -1)
	{
		fd_2 = open(ENV_FILE_2, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
		if (fd_2 == -1)
			return (error_occur_std(FILE_OPEN_ERR));	
		visited = 0;
		while (get_next_line(fd, &line) > 0)
		{
			if (is_empty(line))
				continue ;
			if (!visited && is_duplicate(line, key))
			{
				visited = 1;
				write_new_line(fd_2, key, value);
			}
			else
				ft_putstr_fd(line, fd_2);
			ft_putchar_fd('\n', fd_2);
			ft_free(line);
		}
		// 마지막 문자가 중복인지 체크한다. 중복이면 바꿔주면 끝이다.
		if (!visited && is_duplicate(line, key))
			write_new_line(fd_2, key, value);
		else
		{
			// 중복이 아니면, 마지막 놈을 쓴 다음에, visited를 안했을 때만 key, value값을 추가한다.
			ft_putstr_fd(line, fd_2);
			if (!visited)
			{
				ft_putchar_fd('\n', fd_2);
				write_new_line(fd_2, key, value);
			}
		}
		ft_free(line);
		ft_close(fd);
		ft_close(fd_2);
		if (unlink(ENV_FILE) == -1)
			error_occur_std(UNLINK_ERR);
	}
	return (1);
}

int remove_env_var(char *var)
{
	int fd;
	int visited;
	int fd_2;
	char *line;

	line = 0;
	fd = open(ENV_FILE, O_RDONLY, S_IRWXU); // -1이여도 return (1)되고있음.
	if (fd != -1)
	{
		fd_2 = open(ENV_FILE_2, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
		if (fd_2 == -1)
			return (error_occur_std(FILE_OPEN_ERR));
		visited = 0;
		while (get_next_line(fd, &line) > 0)
		{
			if (!visited && is_duplicate(line, var))
				visited = 1;
			else
				ft_putendl_fd(line, fd_2);
			ft_free(line);
		}
		// 마지막 line이 중복이 아닌 경우에만 add한다.
		// visited를 보면은.. 중간에 중복찾았을 때는 마지막 문자를 append못해서 빼줘야 함.
		// 이 때, 마지막이 중복이면 개행 남아있게 됨.
		if (!is_duplicate(line, var))
			ft_putstr_fd(line, fd_2);
		ft_free(line);
		ft_close(fd);
		ft_close(fd_2);
		if (unlink(ENV_FILE) == -1)
			error_occur_std(UNLINK_ERR);
	}
	return (1);
}

int	write_env_file(t_info *info, char *key, char *value)
{
	if (!evnp_to_envp2(key, value))
		return (0);
	if (!temp_to_datafile(ENV_FILE_2, ENV_FILE))
		return (0);
	return (1);
}