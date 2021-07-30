#include "../includes/minishell.h"

char	*space_filter(char *input, int len)
{
	int		s;
	int		e;
	int		idx;
	char	*new_input;

	new_input = (char *)malloc(sizeof(char) * (len + 1));
	ft_memset(new_input, 0, len + 1);
	if (!new_input)
		error_occur_std(MALLOC_ERR);
	s = 0;
	idx = 0;
	while (new_input && input[s])
	{
		e = s;
		while (input[e] && input[e] == ' ')
			e++;
		if (s != e && s != 0 && input[e])
			new_input[idx++] = ' ';
		new_input[idx++] = input[e];
		if (s != e)
			s = e;
		s++;
	}
	return (new_input);
}

int	append_command(t_info *info, char *input, int s, int e)
{
	char	*temp;
	char	*temp_2;
	t_list	*data;

	temp = ft_substr(input + s, 0, e - s);
	if (!temp)
		return (error_occur_std(MALLOC_ERR));
	temp_2 = space_filter(temp, ft_strlen(temp));
	if (!temp_2)
		return (error_occur_std(MALLOC_ERR));
	free(temp);
	if (ft_strcmp(temp_2, "") == 0)
	{
		free(temp_2);
		return (1);
	}
	data = ft_lstnew(temp_2);
	if (!data)
		return (error_occur_std(MALLOC_ERR));
	if (info->command_cnt == 0)
		info->commands = data;
	else
		ft_lstadd_back(&info->commands, data);
	info->command_cnt++;
	return (1);
}

/*
	substr end point 찾기

	end point
	 - [", '] 나온 경우
	  => 동일한 문자 만날때까지
	 - [", '] 나오지 않은 경우
	  => [|, eof] 까지.
*/
void	move_end_point(t_info *info, char *line, int *e, char end_c)
{
	int idx;

	idx = *e + 1;
	while (line[idx] && line[idx] != end_c)
		idx++;
	if (line[idx] == end_c)
		idx++;
	*e = idx;
}


int	make_command_list(t_info *info, char *input)
{
	int	s;
	int	e;

	s = 0;
	e = 0;
	while (input[e])
	{
		if (input[e] == SINGLE_Q || input[e] == DOUBLE_Q)
			move_end_point(info, input, &e, input[e]);
		else if (input[e] == '|')
		{
			if (!append_command(info, input, s, e))
				return (0);
			s = e + 1;
		}
		e++;
	}
	if (!append_command(info, input, s, e))
		return (0);	
	return (1);
}
