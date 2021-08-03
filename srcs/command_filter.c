#include "../includes/minishell.h"

void	space_filter(char **input, char *new_input)
{
	int		s;
	int		e;
	int		idx;

	s = 0;
	idx = 0;
	while (new_input && (*input)[s])
	{
		e = s;
		while ((*input)[e] && (*input)[e] == ' ')
			e++;
		if (s != e && s != 0 && (*input)[e])
			new_input[idx++] = ' ';
		new_input[idx++] = (*input)[e];
		if (s != e)
			s = e;
		s++;
	}
	free(*input);
	*input = new_input;
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

int	command_filter(t_info *info, char **content)
{
	char	*new_input;
	int		len;

	if (!filter_input(info, content))
		return (error_occur_std(FILTER_INPUT_ERR));
	len = ft_strlen((char *)(*content));
	new_input = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_input)
		return (error_occur_std(MALLOC_ERR));
	ft_memset(new_input, 0, len + 1);
	space_filter(content, new_input);
	return (1);
}