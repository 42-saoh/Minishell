#include "../includes/minishell.h"

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

int	redirect_filter(t_info *info, char **content)
{
	int	i;

	i = 0;
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
