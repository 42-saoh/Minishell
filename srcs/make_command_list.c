#include "../includes/minishell.h"

t_list	*get_numpoint(int num)
{
	t_list	*data;
	int		*ptr;

	ptr = (int *)malloc(sizeof(int));
	if (!ptr)
		return (0);
	data = ft_lstnew(ptr);
	return (data);
}

int		append_command(t_info *info, char *input, int s, int e)
{
	char	*temp;
	t_list	*data;

	temp = ft_substr(input + s, 0, e - s);
	if (!temp)
		return (error_occur_std(MALLOC_ERR));
	if (is_empty(temp))
	{
		free(temp);
		return (0);
	}
	data = ft_lstnew(temp);
	if (!data)
	{
		free(temp);
		return (error_occur_std(MALLOC_ERR));
	}
	ft_lstadd_back(&info->commands, data);
	info->command_cnt++;
	return (1);
}

int		append_pipe_command(t_info *info, char *input, int *s, int *e)
{
	if (input[*e + 1] == PIPE)
	{
		if (!append_command(info, input, *s, *e))
			return (0);
		ft_lstadd_back(&info->commands_symbol, get_numpoint(DB_PIPE));
		*s = *e + 2;
		*e = *e + 1;
	}
	else
	{
		if (!append_command(info, input, *s, *e))
			return (0);
		ft_lstadd_back(&info->commands_symbol, get_numpoint(SG_PIPE));
		*s = *e + 1;
	}
	return (1);
}

int		append_amper_command(t_info *info, char *input, int *s, int *e)
{
	if (input[*e + 1] == '&')
	{
		if (!append_command(info, input, *s, *e))
			return (0);
		ft_lstadd_back(&info->commands_symbol, get_numpoint(DB_AMPER));
		*s = *e + 2;
		*e = *e + 1;
	}
	else
	{
		if (*e == 0)
			return (0);
		if (input[*e - 1] != '>' && input[*e - 1] != '<')
			return (0);
	}
	return (1);
}

int		move_end_point(char *line, int *e, char end_c)
{
	int idx;

	idx = *e + 1;
	while (line[idx] && line[idx] != end_c)
		idx++;
	if (!line[idx])
		return (error_occur_std(NOT_CLOSED));
	*e = idx;
	return (1);
}

int		init_default(t_info *info)
{
	info->command_cnt = 0;
	info->is_builtin = -1;
	if (pipe(info->pipe_out) == -1)
		return (error_occur_perror(PIPE_ERR));
	return (1);
}

int		make_command_list(t_info *info, char *input)
{
	int	s;
	int	e;
	int	len;
	/// 만약 함수의 줄수가 넘는다면 s, e, len 을 포함하는 구조체를 만들고
	/// init_defualt 에서 초기화를 한다면 5칸을 줄일 수 있다.
	s = 0;
	e = 0;
	len = ft_strlen(input);
	init_default(info);
	while (e < len && input[e])
	{
		if (is_quotation(input[e]) && !move_end_point(input, &e, input[e]))
			return (2);
		else if (input[e] == PIPE)
		{
			if (!append_pipe_command(info, input, &s, &e))
				return (0);
		}
		else if (input[e] == '&')
		{
			if (!append_amper_command(info, input, &s, &e))
				return (0);
		}
		e++;
	}
	if (!append_command(info, input, s, e))
		return (0);	
	return (1);
}
