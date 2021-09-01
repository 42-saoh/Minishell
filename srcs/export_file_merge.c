/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_file_merge.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 00:38:01 by taesan            #+#    #+#             */
/*   Updated: 2021/09/01 17:20:33 by taekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	append_export_list(t_info *info, t_list **list, char *line)
{
	t_list	*data;
	char	*content;

	if (!line)
		return (0);
	content = ft_strjoin(line, "\n");
	ft_free(line);
	if (!content)
		return (0);
	data = ft_lstnew(content);
	if (!data)
		return (0);
	ft_lstadd_back(list, data);
	info->envp_cnt++;
	return (1);
}

int	envp_add_var(t_info *info, t_list **list)
{
	t_list	*list_temp;
	char	**envp;
	int		i;

	envp = (char **)malloc(sizeof(char *) * (info->envp_cnt + 1));
	if (!envp)
		return (0);
	envp[info->envp_cnt] = 0;
	i = 0;
	while (info->envp[i])
	{
		envp[i] = info->envp[i];
		i++;
	}
	ft_free(info->envp);
	list_temp = *list;
	while (list_temp)
	{
		envp[i] = (char *)(list_temp->content);
		list_temp = list_temp->next;
		i++;
	}
	info->envp = envp;
	return (1);
}

int	export_file_merge(t_info *info, t_list **list)
{
	int		fd;
	char	*line;

	fd = open(EXPORT_FILE, O_RDONLY);
	if (fd != -1)
	{
		line = 0;
		while (get_next_line(fd, &line) > 0)
		{
			if (!append_export_list(info, list, line))
				return (0);
		}
		if (!append_export_list(info, list, line))
			return (0);
		if (!envp_add_var(info, list))
			return (0);
		ft_close(fd);
	}
	return (1);
}
