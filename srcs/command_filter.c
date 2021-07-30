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
/*
	str의 s ~ e범위에 존재하는 $를 치환한 새로운 문자열로 변경한다.

	다음 탐색 인덱스 (e)를 여기서 함께 변경해준다.
*/
int		replace_env(char **envp, char **ptr, int s, int *next_idx)
{
	int i;
	char *result;

	result = 0;
	// printf("str : [%s], idx : [%d], (*ptr) + s : [%s]\n", *ptr, s, (*ptr) + s);
	while (*envp)
	{
		i = 0;
		while ((*envp)[i] && (*ptr)[s + i + 1] && ((*envp)[i] == (*ptr)[s + i + 1]))
			i++;
		if ((*envp)[i] == '=')
		{
			int len = ft_strlen(*envp + i + 1);
			char *value = ft_substr(*envp + i + 1, 0, len);
			
			// printf("value : [%s], len : %d\n", value, len);

			char *front = ft_substr(*ptr, 0, s);
			// printf("front : [%s]\n", front);

			// $ 미만까지 substr
			// s + i + 1
			len = ft_strlen(*ptr);
			char *back = ft_substr(*ptr + s + i + 1, 0, len - i);
			// printf("back : [%s]\n", back);

			char *temp = ft_strjoin(front, value);
			*next_idx = ft_strlen(temp);
			result = ft_strjoin(temp, back);

			// printf("replace result : [%s]\n", result);
			// printf("[%s]\n", *ptr + i + 1);
			break ;
		}
		envp++;
	}
	if (result)
	{
		free(*ptr);
		*ptr = result;
	}
	// replace 된 경우에는 다시 처음부터 변경될 수 있도록.
	return (1);
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
			// printf("before : [%s]\n", *input);
			if ((*input)[s] == (*input)[e])
			{
				if (!quote_filter(info, input, s, &e))
					return (0);
			}
			// printf("after : [%s]\n", *input);
		}
		else if ((*input)[e] == DOLLAR)
		{
			// printf("before : [%s]\n", input);
			if (!replace_env(info->envp, input, e, &e))
				return (0);
			// printf("after : [%s]\n", input);
		}
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
		printf("cmd : [%s]\n", info->commands->content);
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
		printf("final : [%s]\n", info->commands->content);
		info->commands = info->commands->next;
	}
	return (0);
}