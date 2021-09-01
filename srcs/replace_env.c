#include "../includes/minishell.h"

char	*get_dollar_value(char **envp, char *input)
{
	int	i;
	int	exist;

	while (*envp)
	{
		i = 0;
		exist = 1;
		while (pass_possible(input[i]))
		{
			if (!(*envp)[i] || (*envp)[i] != input[i])
			{
				exist = 0;
				break ;
			}
			i++;
		}
		if (exist && (*envp)[i] != '=')
			exist = 0;
		if (exist)
			return (*envp + i + 1);
		envp++;
	}
	return ("");
}

char	*make_new_input(char *input, int s, int *next_idx, char *value)
{
	char	*front;
	char	*back;
	char	*join;
	char	*result;

	result = 0;
	front = ft_substr(input, 0, s);
	if (!front)
		return (0);
	join = ft_strjoin(front, value);
	free(front);
	if (!join)
		return (0);
	*next_idx = ft_strlen(join);
	while (pass_possible(input[s]))
		s++;
	back = ft_substr(input + s, 0, ft_strlen(input) - s);
	result = ft_strjoin(join, back);
	if (back)
		free(back);
	free(join);
	return (result);
}

/*
	str의 s ~ e범위에 존재하는 $를 치환한 새로운 문자열로 변경한다.
	다음 탐색 인덱스 (e)를 여기서 함께 변경해준다.
*/
int	replace_env(char **envp, char **ptr, int s, int *next_idx)
{
	char	*value;
	char	*result;

	value = get_dollar_value(envp, *ptr + s + 1);
	result = make_new_input(*ptr, s, next_idx, value);
	if (!result)
		return (error_occur_perror(MAKE_NEW_INPUT_ERR));
	free(*ptr);
	*ptr = result;
	return (1);
}
