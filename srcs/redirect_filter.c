#include "../includes/minishell.h"

/*
	list에 넣어놓고,
	몇번째 명령어껀지 구분 되어야 함.
*/

/*
	append도 봐야 함
	heredoc도 봐야 함
*/
// void	set_right_fd(t_redirection *data, char *content, int *e)
// {
// 	int	i;

// 	i = *e + 1;
// 	// heredoc or append인 경우
// 	if (content[i] && content[i] == content[*e])
// 	{

// 	}
// 	// 공백제거
// 	while (content[i] && content[i] == ' ')
// 		i++;
// 	// 
// 	if (content[i] == '&')
// 	{

// 	}
// }

/*
	왼쪽대상 찾기. 바로옆에 딱 붙어서 숫자여야 함.
*/
// void	set_left_fd(t_redirection *data, char *content, int *s)
// {
// 	int i;
// 	int	end;
// 	int fd;
	
// 	i = *s - 1;
// 	fd = 0;
// 	while(i >= 0 && ft_isdigit(content[i]))
// 		i--;
// 	if (i < *s - 1 && (i < 0 || (i >= 0 && content[i] == ' ')))
// 	{
// 		i++;
// 		end = *s;
// 		*s = i;
// 		while (i < end)
// 		{
// 			fd = (fd * 10) + (content[i] - '0'); 
// 			i++;
// 		}
// 		data->left_fd = fd;
// 	}
// }

// int	temp_func(t_info *info, char **content, int s, char dir)
// {
// 	t_list			*list;
// 	t_list			*data;
// 	t_redirection	*redirect;
// 	int				e;

// 	redirect = (t_redirection *)malloc(sizeof(t_redirection));
// 	if (!redirect)
// 		return (0);
// 	data = ft_lstnew(redirect);
// 	if (!data)
// 		return (0);
// 	if (dir == REDIRECT_IN)
// 	{
// 		list = info->in;
// 		redirect->left_fd = 0;
// 	}
// 	else if (dir == REDIRECT_OUT)
// 	{
// 		list = info->out;
// 		redirect->left_fd = 1;
// 	}
// 	e = s;
// 	printf("before => start : [%d], left_fd : [%d]\n", s, redirect->left_fd);
// 	set_left_fd(redirect, *content, &s);
// 	printf("after => start : [%d], left_fd : [%d]\n", s, redirect->left_fd);
// 	// if (content[e + 1] && dir == content[e + 1])
// 	// {
// 	// 	if (e ==)
// 	// 	// here_doc or append
// 	// }
// 	// // right fd받아오고, e포인트를 변경.
// 	// printf("before => end : [%d], right_fd : [%d]\n", e, redirect->right_fd);
// 	// set_right_fd(&data, *content, &e);
// 	// printf("after => end : [%d], right_fd : [%d]\n", e, redirect->right_fd);
	
// 	// substr
// 	return (0);
// }

int	redirect_filter(t_info *info, char **content)
{
	int i;

	i = 0;
	while ((*content)[i])
	{
		if (is_redirect((*content)[i]))
		{
			if ((*content)[i] == REDIRECT_IN && \
				!redirect_in_add(info, content, i, REDIRECT_IN))
					return (0);
			else if ((*content)[i] == REDIRECT_OUT && \
				!redirect_out_add(info, content, i, REDIRECT_OUT))
					return (0);
			i = -1;
		}
		i++;
	}
	return (1);
}