/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 01:34:38 by taesan            #+#    #+#             */
/*   Updated: 2021/08/31 20:32:39 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	file_to_envp(t_info *info)
{
	int		fd;
	int		idx;
	char	*line;

	info->envp = (char **)malloc(sizeof(char *) * (info->envp_cnt + 1));
	if (!info->envp)
		return (0);
	info->envp[info->envp_cnt] = 0;
	fd = open(ENV_FILE, O_RDONLY);
	if (fd == -1)
		return (error_occur_perror(FILE_OPEN_ERR));
	idx = 0;
	while (get_next_line(fd, &line) > 0 && idx < info->envp_cnt)
	{
		info->envp[idx] = line;
		if (!info->envp[idx])
			return (0);
		idx++;
	}
	info->envp[idx] = ft_strdup(line);
	if (!info->envp[idx])
		return (0);
	ft_free(line);
	ft_close(fd);
	return (1);
}

int	count_envp_len(t_info *info)
{
	int		fd;
	char	*line;

	fd = open(ENV_FILE, O_RDONLY);
	if (fd == -1)
		return (error_occur_perror(FILE_OPEN_ERR));
	while (get_next_line(fd, &line) > 0)
	{
		info->envp_cnt++;
		ft_free(line);
	}
	info->envp_cnt++;
	ft_free(line);
	ft_close(fd);
	return (1);
}

void	clear_envp_info(t_info *info)
{
	int	i;

	if (!info->envp)
		return ;
	i = 0;
	while (info->envp[i])
		ft_free(info->envp[i++]);
	ft_free(info->envp);
	info->envp_cnt = 0;
}

int	copy_envp(t_info *info)
{
	clear_envp_info(info);
	if (!count_envp_len(info))
		return (0);
	return (file_to_envp(info));
}
