#include "../includes/minishell.h"

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
		return (1);
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

void	move_end_point(char *line, int *e, char end_c)
{
	int idx;

	idx = *e + 1;
	while (line[idx] && line[idx] != end_c)
		idx++;
	if (line[idx] == end_c)
		idx++;
	*e = idx;
}

int		make_command_list(t_info *info, char *input)
{
	int	s;
	int	e;

	s = 0;
	e = 0;
	info->command_cnt = 0;
	info->is_builtin = -1;
	while (input[e])
	{
		if (is_quotation(input[e]))
			move_end_point(input, &e, input[e]);
		else if (input[e] == PIPE)
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
