/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:49:55 by taesan            #+#    #+#             */
/*   Updated: 2021/08/02 17:00:51 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	따옴표 처리
*/
int	set_command_info(t_info *info, char *input)
{
	char	**input_sp;
	char	*cmd;
	char 	**temp;
	int		cmd_idx;

	printf("input : [%s]\n", input);
	input_sp = ft_split(input, ' ');
	if (!input_sp)
	{
		printf("#1\n");
		return (error_occur_std(SPLIT_ERR));
	}
	printf("input_sp[0] : [%s]\n", input_sp[0]);
	temp = ft_split(input_sp[0], '/');
	if (!temp)
	{
		printf("#2\n");
		return (error_occur_std(SPLIT_ERR));
	}
	cmd_idx = 0;
	while (temp[cmd_idx])
		cmd_idx++;
	info->is_builtin = check_builtin(temp[cmd_idx - 1]);
	split_free(temp);
	cmd = check_command(info->paths, input_sp[0], ft_strlen(input_sp[0]));
	if (cmd)
	{
		free(input_sp[0]);
		input_sp[0] = cmd;
	}
	info->param = input_sp;
	return (1);
}

int	init_pipe(const char *input, const char *output, char *envp[], t_pipe *info)
{
	int	fd;

	info->param = 0;
	info->out_file = output;
	if (pipe(info->pipe_in) == -1)
		return (error_occur_perror(PIPE_ERR));
	if (pipe(info->pipe_out) == -1)
		return (error_occur_perror(PIPE_ERR));
	info->result_fd = open(output, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, \
							S_IRUSR | S_IWUSR);
	if (info->result_fd == -1)
		return (error_occur_perror(OUTPUT_OPEN_ERR));
	info->envp = envp;
	fd = open(input, O_RDONLY);
	if (fd == -1)
		return (error_occur_perror(INPUT_OPEN_ERR));
	dup2(fd, info->pipe_in[READ_FD_IDX]);
	close(fd);
	close(info->pipe_in[WRITE_FD_IDX]);
	return (1);
}

char	**init_path(char *envp[])
{
	char	*path;
	char	**paths;

	path = 0;
	while (*envp)
	{
		path = *envp;
		if (ft_strlen(path) < 4)
			continue ;
		if (path[0] == 'P' && path[1] == 'A' && \
				path[2] == 'T' && path[3] == 'H')
		{
			path = *envp;
			break ;
		}
		envp++;
	}
	if (!path)
		path = PATH;
	paths = ft_split(path + 5, ':');
	if (!paths)
		error_occur_std(SPLIT_ERR);
	return (paths);
}
