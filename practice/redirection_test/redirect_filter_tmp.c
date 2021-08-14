#include "../../includes/minishell.h"

void	ft_free(void *data)
{
	if (!data)
		return ;
	free(data);
	data = 0;
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;

	if (!s)
		return (0);
	if (!(dst = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	if (start >= ft_strlen(s))
		ft_strlcpy(dst, "", 2);
	else
		ft_strlcpy(dst, (s + start), len + 1);
	return (dst);
}
size_t		ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t src_len;
	size_t i;

	if (!src)
		return (0);
	src_len = 0;
	while (src[src_len])
		src_len++;
	if (!dest)
		return (src_len);
	if (dstsize)
	{
		i = 0;
		while (src[i] && i + 1 < dstsize)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (src_len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	int		s1_len;
	int		s2_len;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!(dst = (char *)malloc(s1_len + s2_len + 1)))
		return (0);
	ft_strlcpy(dst, s1, (s1_len + 1));
	ft_strlcpy(dst + s1_len, s2, (s2_len + 1));
	return (dst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *last;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		last = ft_lstlast(lst[0]);
		last->next = new;
	}
}

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	if (!(list = (t_list *)malloc(sizeof(t_list))))
		return (0);
	list->content = content;
	list->next = NULL;
	return (list);
}

int		remove_redirect(int s, int e, char **content)
{
	char *left;
	char *right;
	char *new_input;

	new_input = 0;
	left = ft_substr(*content, 0, s);
	if (left)
	{
		right = ft_substr(*content + e, 0, ft_strlen(*content) - e);
		if (right)
		{
			new_input = ft_strjoin(left, right);
			ft_free(right);
		}
		ft_free(left);
	}
	if (!new_input)
		return (0);
	ft_free(*content);
	*content = new_input;
	return (1);
}

void	move_quot_point(char *line, int *e, char end_c)
{
	int idx;

	idx = *e + 1;
	while (line[idx] != end_c)
		idx++;
	*e = idx + 1;
}

int	move_redirect_space(char *content, int *e, int idx)
{
	int	t_idx;

	t_idx = idx + 1;
	while (content[t_idx] && content[t_idx] == ' ')
		t_idx++;
	if (!content[t_idx])
		return (0);
	while (content[t_idx] && content[t_idx] != ' ')
	{
		if (content[t_idx] == SINGLE_Q || content[t_idx] == DOUBLE_Q)
			move_quot_point(content, &t_idx, content[t_idx]);
		else
			t_idx++;
	}
	*e = t_idx;
	return (1);
}

int	move_redirect_and(char *content, int *e, int idx)
{
	int t_idx;

	t_idx = idx + 1;
	while (content[t_idx] && content[t_idx] != ' ')
	{
		if (content[t_idx] == SINGLE_Q || content[t_idx] == DOUBLE_Q)
			move_quot_point(content, &t_idx, content[t_idx]);
		t_idx++;
	}
	if (t_idx == idx + 1)
		return (move_redirect_space(content, e, idx));
	*e = t_idx;
	return (1);
}

int	move_db_redirect_out(char *content, int *e)
{
	int	idx;

	idx = *e + 2;
	if (!content[idx])
		return (0);
	else if (content[idx] == REDIRECT_IN || content[idx] == REDIRECT_OUT)
		return (0);
	else if (content[idx] == '&')
		return (move_redirect_and(content, e, idx));
	else if (content[idx] == ' ')
		return (move_redirect_space(content, e, idx));
	else
	{
		while (content[idx] && content[idx] != ' ')
		{
			if (content[idx] == SINGLE_Q || content[idx] == DOUBLE_Q)
				move_quot_point(content, &idx, content[idx]);
			else
				idx++;
		}
		*e = idx;
	}
	return (1);
}

int	move_db_redirect_in(char *content, int *e)
{
	int	idx;

	idx = *e + 2;
	if (!content[idx])
		return (0);
	else if (content[idx] == REDIRECT_IN || content[idx] == REDIRECT_OUT)
		return (0);
	else if (content[idx] == '&')
		return (0);
	else if (content[idx] == ' ')
		return (move_redirect_space(content, e, idx));
	else
	{
		while (content[idx] && content[idx] != ' ')
		{
			if (content[idx] == SINGLE_Q || content[idx] == DOUBLE_Q)
				move_quot_point(content, &idx, content[idx]);
			else
				idx++;
		}
		*e = idx;
	}
	return (1);
}

int	move_sg_redirect_in(char *content, int *e)
{
	int	idx;

	idx = *e + 1;
	if (!content[idx])
		return (0);
	else if (content[idx] == REDIRECT_OUT)
		return (0);
	else if (content[idx] == '&')
		return (move_redirect_and(content, e, idx));
	else if (content[idx] == ' ')
		return (move_redirect_space(content, e, idx));
	else
	{
		while (content[idx] && content[idx] != ' ')
		{
			if (content[idx] == SINGLE_Q || content[idx] == DOUBLE_Q)
				move_quot_point(content, &idx, content[idx]);
			else
				idx++;
		}
		*e = idx;
	}
	return (1);
}

int	move_sg_redirect_out(char *content, int *e)
{
	int	idx;

	idx = *e + 1;
	if (!content[idx])
		return (0);
	else if (content[idx] == REDIRECT_OUT)
		return (0);
	else if (content[idx] == '&')
		return (move_redirect_and(content, e, idx));
	else if (content[idx] == ' ')
		return (move_redirect_space(content, e, idx));
	else
	{
		while (content[idx] && content[idx] != ' ')
		{
			if (content[idx] == SINGLE_Q || content[idx] == DOUBLE_Q)
				move_quot_point(content, &idx, content[idx]);
			else
				idx++;
		}
		*e = idx;
	}
	return (1);
}

int	redirect_get_end(char *content, int *e)
{
	int i;

	if (content[*e] == REDIRECT_IN && content[*e + 1] == REDIRECT_IN)
		i = move_db_redirect_in(content, e);
	else if (content[*e] == REDIRECT_OUT && content[*e + 1] == REDIRECT_OUT)
		i = move_db_redirect_out(content, e);
	else if (content[*e] == REDIRECT_IN)
		i = move_sg_redirect_in(content, e);
	else if (content[*e] == REDIRECT_OUT)
		i = move_sg_redirect_out(content, e);
	else
		i = 0;
	return (i);
}

int	redirect_add(t_info *info, char **content, int *i)
{
	int	s;
	int	e;

	s = 1;
	e = *i;
	while (*i >= s)
	{
		if ((*content)[e - s] >= '0' && (*content)[e - s] <= '9')
			s++;
		else
			break ;
	}
	if (e >= s && (*content)[e - s] != ' ')
		s = 1;
	s = e - s + 1;
	if (!redirect_get_end(*content, &e))
		return (0);
	ft_lstadd_back(&info->redirect_lst, ft_lstnew(ft_substr(*content, s, e - s)));
	*i = s;
	return (remove_redirect(s, e, content));
}

int	redirect_filter_tmp(t_info *info, char **content)
{
	int	i;

	i = 0;
	info->redirect_lst = 0;
	while ((*content)[i])
	{
		if ((*content)[i] == SINGLE_Q || (*content)[i] == DOUBLE_Q)
			move_quot_point(*content, &i, (*content)[i]);
		else if ((*content)[i] == REDIRECT_IN || (*content)[i] == REDIRECT_OUT)
		{
			if (!redirect_add(info, content, &i))
				return (0);
		}
		else
			i++;
	}
	return (1);
}

int main()
{
	t_info info;
	int		i;
	char	*a;

	int fd = open("testcase.txt", O_RDONLY);
	dup2(fd, 0);

	a = readline("test : ");
	int tc = 1;
	// # 8번 케이스 
	while (a) 
	{
		printf("\x1b[32m" "================ case %d : [%s] ================\n" "\x1b[0m",tc++, a);
		i = redirect_filter_tmp(&info, &a);
		printf("command : [%s]\n", a);
		int cnt = 0;
		while(a && info.redirect_lst)
		{
			printf("redirection(%d): [%s]\n",cnt++, (char *)info.redirect_lst->content);
			info.redirect_lst = info.redirect_lst->next;
		}
		a = readline("test : ");
	}
}
