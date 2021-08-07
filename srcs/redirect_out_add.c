#include "../includes/minishell.h"

int		file_open_getfd_out(char *content, int *e, int is_append)
{
	char	*file_nm;
	int		fd;

	file_nm = get_right_str(content, e);
	if (!file_nm)
		return (0);
	if (is_append)
		fd = open(file_nm, O_WRONLY | O_CREAT | O_APPEND, \
					S_IRUSR | S_IWUSR);
	else	
		fd = open(file_nm, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, \
							S_IRUSR | S_IWUSR);
	ft_free(file_nm);
	if (fd == -1)
		return (error_occur_perror(OUTPUT_OPEN_ERR));
	return (fd);
}

int		set_right_fd_out(t_redirect_out *data, char *content, int *e)
{
	int		i;
	int		s;
	int		fd;

	i = *e + 1;
	while (content[i] && content[i] == ' ')
		i++;
	if (!data->is_append && content[i] == '&')
	{
		i++;
		s = i;
		while (content[i] && ft_isdigit(content[i]))
			i++;
		data->right_fd = get_fd(s, i, content);
		*e = i;
	}
	else
	{
		data->right_fd = file_open_getfd_out(content, e, data->is_append);
		if (!data->right_fd)
			return (0);
	}
	return (1);
}

/*
	왼쪽대상 찾기. 바로옆에 딱 붙어서 숫자여야 함.
*/
void	set_left_fd_out(t_redirect_out *data, char *content, int *s)
{
	int i;
	int	end;
	int fd;
	
	i = *s - 1;
	fd = 0;
	while(i >= 0 && ft_isdigit(content[i]))
		i--;
	if (i < *s - 1 && (i < 0 || (i >= 0 && content[i] == ' ')))
	{
		data->left_fd = get_fd(i + 1, *s, content);
		*s = i + 1;
	}
}

t_redirect_out	*append_out_data(t_info *info)
{
	t_redirect_out	*redirect;
	t_list			*data;

	redirect = (t_redirect_out *)malloc(sizeof(t_redirect_out));
	if (!redirect)
		return (0);
	ft_bzero(redirect, sizeof(t_redirect_out));
	data = ft_lstnew(redirect);
	if (!data)
	{
		ft_free(redirect);
		return (0);
	}
	redirect->left_fd = 1;
	ft_lstadd_back(&info->out, data);
	return (redirect);
}
/*
	현재 content의 start부터 좌, 우로 입출력 변경 대상을 찾고
	list에 추가해준다.
*/
int	redirect_out_add(t_info *info, char **content, int s, char dir)
{
	int				e;
	t_redirect_out	*redirect;

	redirect = append_out_data(info);
	if (!redirect)
		return (0);
	e = s;
	set_left_fd_out(redirect, *content, &s);
	if ((*content)[e + 1] && dir == (*content)[e + 1])
	{
		e++;
		redirect->is_append = 1;
	}
	set_right_fd_out(redirect, *content, &e);
	return (remove_redirect(s, e, content));
}