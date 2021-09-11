/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_asterisk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 01:25:08 by taesan            #+#    #+#             */
/*   Updated: 2021/09/01 17:20:45 by taekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	rebuild_param(t_info *info, t_list **list)
{
	t_list	*temp;
	char	**new_param;
	int		i;

	info->param_cnt = ft_lstsize(*list) + 1;
	new_param = (char **)malloc(sizeof(char *) * (info->param_cnt + 1));
	if (!new_param)
		return (0);
	new_param[0] = info->param[0];
	new_param[info->param_cnt] = 0;
	temp = *list;
	i = 1;
	while (temp)
	{
		new_param[i++] = (char *)temp->content;
		temp = temp->next;
	}
	ft_lstclear(list, content_not_rm);
	ft_free(info->param);
	info->param = new_param;
	return (1);
}

int	pattern_check(char *pattern, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (pattern[i])
	{
		if (pattern[i] && pattern[i] == '*')
		{
			while (pattern[i] && pattern[i] == '*')
				i++;
			if (!pattern[i])
				return (1);
			while (line[j] && line[j] != pattern[i])
				j++;
		}
		if (pattern[i] != line[j])
			return (0);
		i++;
		j++;
	}
	if (pattern[i] != line[j])
		return (0);
	return (1);
}

int	append_asterisk_name(char *param, t_list **list, DIR *dir_ptr)
{
	struct dirent	*file;
	char			*content;
	t_list			*data;
	int				append;

	file = readdir(dir_ptr);
	append = -1;
	while (file)
	{
		if (file->d_name[0] != '.' && pattern_check(param, file->d_name))
		{
			content = ft_strdup(file->d_name);
			if (!content)
				return (0);
			data = ft_lstnew(content);
			if (!data)
				ft_free(content);
			if (!data)
				return (0);
			ft_lstadd_back(list, data);
			append = 1;
		}
		file = readdir(dir_ptr);
	}
	return (append);
}

int	add_new_p_list(t_info *info, char **param, t_list **list, int is_ast)
{
	DIR		*dir_ptr;
	t_list	*data;
	int		r;

	r = 1;
	dir_ptr = opendir(".");
	if (!dir_ptr)
		r = 0;
	if (r && is_ast)
	{
		info->asterisk_check = 1;
		r = append_asterisk_name(*param, list, dir_ptr);
	}
	if (!is_ast || r == -1)
	{
		data = ft_lstnew(*param);
		if (!data)
			r = 0;
		ft_lstadd_back(list, data);
	}
	if (!r)
		ft_lstclear(list, ft_free);
	closedir(dir_ptr);
	return (r);
}

int	filter_asterisk(t_info *info, int i)
{
	t_list	*list;
	int		j;
	int		is_asterisk;

	list = 0;
	while (info->param[i])
	{
		is_asterisk = 0;
		j = 0;
		while (info->param[i][j])
		{
			if (info->param[i][j] == '*')
			{
				is_asterisk = 1;
				if (!add_new_p_list(info, &info->param[i], &list, 1))
					return (0);
				break ;
			}
			j++;
		}
		if (!is_asterisk && !add_new_p_list(info, &info->param[i], &list, 0))
			return (0);
		i++;
	}
	return (rebuild_param(info, &list));
}
