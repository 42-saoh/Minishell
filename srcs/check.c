/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 23:50:42 by taesan            #+#    #+#             */
/*   Updated: 2021/07/31 02:58:53 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*create_new_cmd(char *cmd, int len)
{
	char	*new_cmd;

	new_cmd = (char *)malloc(sizeof(len + 1));
	if (!new_cmd)
		return (0);
	new_cmd[0] = '/';
	ft_strlcpy(new_cmd + 1, cmd, len + 1);
	return (new_cmd);
}

int	exec_file_check(char *path)
{
	struct stat sb;

	if (stat(path, &sb) == -1)
		return (0);
	if (sb.st_mode & S_IXUSR)
		return (1);
	return (0);
}

int	check_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (ECHO);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (CD);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (PWD);
	else if (ft_strcmp(cmd, "export") == 0)
		return (EXPORT);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (UNSET);
	else if (ft_strcmp(cmd, "env") == 0)
		return (ENV);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (EXIT);
	else
		return (NOT_BUILTIN);
}

char	*check_command(char **paths, char *cmd, int len)
{
	char	*full_path;
	char	*new_cmd;
	int		i;

	full_path = 0;
	new_cmd = create_new_cmd(cmd, len);
	if (new_cmd)
	{
		i = 0;
		while (paths[i])
		{
			full_path = ft_strjoin(paths[i], new_cmd);
			if (!full_path || exec_file_check(full_path))
				break ;
			free(full_path);
			full_path = 0;
			i++;
		}
		free(new_cmd);
	}
	return (full_path);
}

int		exist_dollar(char *input, int s, int e)
{
	while (input[s] && s < e)
	{
		if (input[s] == DOLLAR)
			return (s);
		s++;
	}
	return (0);
}
