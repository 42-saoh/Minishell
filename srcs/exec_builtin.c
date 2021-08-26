/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 14:54:24 by taesan            #+#    #+#             */
/*   Updated: 2021/08/26 14:27:10 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//◦ export with no options
// ◦ unset with no options
//◦ env with no options or arguments
#include "../includes/minishell.h"

int	export_errror(char *param)
{
	write(STDERR_FILENO, "export: `", 10);
	ft_putstr_fd(param, STDERR_FILENO);
	ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
	return (0);
}

int	export_add_var(t_info *info, char *param, int j)
{
	char	*key;
	char	*value;
	int		r;

 	key = ft_substr(param, 0, j);
	value = ft_substr(param + j + 1, 0, ft_strlen(param) - j);
	r = 1;
	if (key && value)
	{
		// key가 널인경우는 에러임. ex) a=b =c
		// parent에서하게되면, 그냥 printf써도 무관 함.
		if (ft_strcmp(key, "") == 0 || is_empty(key))
			export_errror(param);
		else
			r = write_env_file(info, key, value);
			// printf("%s=\"%s\"\n", key, value);
		// key가지고 .export 파일도 검사해서 동일한 변수는 값이 생겼으니깐, 지워줘야 함.
		if (r)
			r = write_export_file(key, 1);
	}
	ft_free(key);
	ft_free(value);
	if ((key && !value) || (!key && value)) //substr에서 error된 결과가 들어온 경우
		return (0);
	return (r);
}

/*
	0은 command니깐,
	1부터, r은 중간에 틀리면 끝낼라고
*/
int	write_export(t_info *info)
{
	int	i;
	int j;
	int	r;
	char *param;

	i = 1;
	r = 1;
	while (r && info->param[i])
	{
		param = info->param[i];
		j = 0;
		while (param[j] && param[j] != '=')
			j++;
		if (param[j] == '=')
			r = export_add_var(info, param, j);
		else if (is_empty(param))
			r = export_errror(param);
		else
			r = write_export_file(param, 0);
		i++;
	}
	return (r);
}

int	envp_append_vars(t_info *info, t_list **list)
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

int	append_export_list(t_info *info, t_list **list, char *line)
{
	int		len;
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
/*
	** envp에다가 .export.txt읽어서 붙인다.
*/
int		check_export_file(t_info *info, t_list **list)
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
		if (!envp_append_vars(info, list))
			return (0);
		ft_close(fd);
	}
	return (1);
}

int		builtin_env(t_info *info)
{
	char **envp;

	envp = info->envp;
	while (*envp)
	{
		ft_putendl_fd(*envp, STDOUT_FILENO);
		envp++;
	}
	return (1);
}

int		print_export(t_info *info)
{
	char	**envp;
	int		j;
	int		visit;

	envp = info->envp;
	while (*envp)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		j = 0;
		visit = 0;
		while ((*envp)[j])
		{
			ft_putchar_fd((*envp)[j], STDOUT_FILENO);
			if ((*envp)[j] == '=' && !visit)
			{
				write(STDOUT_FILENO, "\"", 1);
				visit = 1;
			}
			j++;
		}
		if (visit)
			ft_putendl_fd("\"", STDOUT_FILENO);
		envp++;
	}
	return (1);	
}

int		builtin_unset(t_info *info)
{
	int	i;

	i = 1;
	while (info->param[i])
	{
		if (!remove_env_var(info->param[i]))
			return (0);
		if (!temp_to_datafile(ENV_FILE_2, ENV_FILE))
			return (0);
		if (!write_export_file(info->param[i], 1))
			return (0);
		i++;
	}
	return (0);
}
/*
	1. .export.txt파일을 읽은 후 info->envp를 rebuild한다.
	2. 정렬한다.
	3. 출력.
*/
int		builtin_export(t_info *info)
{
	int		i;
	char	**temp;
	t_list	*list;

	// just export !
	if (!info->param[1])
	{
		list = 0;
		if (check_export_file(info, &list))
		{
			temp = (char **)malloc(sizeof(char *) * (info->envp_cnt + 1));
			if (!temp)
				return (0);
			merge_sort(info->envp, temp, 0, info->envp_cnt - 1);
			ft_free(temp);
			print_export(info);
			ft_lstclear(&list, ft_free);
		}
	}
	else
		return (write_export(info));
	return (1);
}

void	exec_builtin(int cmd, t_info *info)
{
	int r;

	if (cmd == EXPORT)
		r = builtin_export(info);
	else if (cmd == UNSET)
		r = builtin_unset(info);
	else if (cmd == ENV)
		r = builtin_env(info);
	if (!r)
		exit(EXEC_FAIL);
	exit(0);
}