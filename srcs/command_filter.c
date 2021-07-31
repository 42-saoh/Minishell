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

int		quote_filter(t_info *info, char **input, int s, int *e)
{
	int		dollar_idx;
	char	is_db_q;

	is_db_q = (*input)[s];
	(*input)[s] = ' ';
	(*input)[*e] = ' ';
	if (is_db_q == DOUBLE_Q)
	{
		dollar_idx = exist_dollar(*input, s, *e);
		if (dollar_idx)
		{
			if(!replace_env(info->envp, input, dollar_idx, e))
				return (0);
		}
	}
	return (1);
}

int	filter_input(t_info *info, char **input)
{
	int		s;
	int		e;

	e = 0;
	while ((*input)[e])
	{
		if (is_quotation((*input)[e]))
		{
			s = e++;
			while ((*input)[e] && (*input)[e] != (*input)[s])
				e++;
			if ((*input)[s] == (*input)[e])
			{
				if (!quote_filter(info, input, s, &e))
					return (0);
			}
		}
		else if ((*input)[e] == DOLLAR && \
			!replace_env(info->envp, input, e, &e))
			return (0);
		e++;
	}
	return (1);
}


int	command_filter(t_info *info)
{
	char	*temp;
	int		len;

	while (info->commands)
	{
		//printf("cmd : [%s]\n", info->commands->content);
		if (!filter_input(info, (char **)&(info->commands->content)))
		{
			printf("filter input error\n");
			return (0);
		}
		len = ft_strlen((char *)info->commands->content);
		temp = space_filter(info->commands->content, len);
		if (!temp)
			return (error_occur_std(MALLOC_ERR));
		info->commands->content = temp;
		// printf("final : [%s]\n", info->commands->content);
		info->commands = info->commands->next;
	}
	return (0);
}