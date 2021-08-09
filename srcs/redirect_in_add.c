#include "../includes/minishell.h"

/*
	이거 open에러일때, 에러출력하고
	main쪽에서는 에러로 판단해서 프로세스 종료하고 있다.
	open이 실패해도 뒤에 코드는 돌아가는지한번더 확인
	일단 안돌아가는 것 같다. f1, f2있을 때
	cat < f1 < f3나 cat < f3 < f1모두 안됨

	=? 
*/
int		file_open_getfd_in(char *content, int *e)
{
	char	*file_nm;
	int		fd;

	file_nm = get_right_str(content, e);
	if (!file_nm)
		return (0);
	fd = open(file_nm, O_RDONLY);
	if (fd == -1)
		printf("%s: %s\n", file_nm, NO_SUCH_FILE);
	ft_free(file_nm);
	return (fd);
}

int		set_right_fd_in(t_redirect_in *data, char *content, int *e)
{
	int		i;
	int		s;
	int		fd;

	i = *e + 1;
	while (content[i] && content[i] == ' ')
		i++;
	if (content[i] == '&')
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
		data->right_fd = file_open_getfd_in(content, e);
		if (data->right_fd == -1)
			return (0);
	}
	return (1);
}

/*
	왼쪽대상 찾기. 바로옆에 딱 붙어서 숫자여야 함.
*/
void	set_left_fd_in(t_redirect_in *data, char *content, int *s)
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

t_redirect_in	*append_in_data(t_info *info)
{
	t_redirect_in	*redirect;
	t_list			*data;

	redirect = (t_redirect_in *)malloc(sizeof(t_redirect_in));
	if (!redirect)
		return (0);
	ft_bzero(redirect, sizeof(t_redirect_in));
	data = ft_lstnew(redirect);
	if (!data)
	{
		ft_free(redirect);
		return (0);
	}
	redirect->left_fd = 0;
	ft_lstadd_back(&info->in, data);
	return (redirect);
}
/*
	현재 content의 start부터 좌, 우로 입출력 변경 대상을 찾고
	list에 추가해준다.
*/
int	redirect_in_add(t_info *info, char **content, int s, char dir)
{
	int				e;
	t_redirect_in	*redirect;

	redirect = append_in_data(info);
	if (!redirect)
		return (0);
	e = s;
	set_left_fd_in(redirect, *content, &s);
	if ((*content)[e + 1] && dir == (*content)[e + 1])
	{
		e++;
		redirect->limiter = get_right_str(*content, &e);
		if (!redirect->limiter)
			return (0);
	}
	else
		if (!set_right_fd_in(redirect, *content, &e))
			return (0);
	return (remove_redirect(s, e, content));
}