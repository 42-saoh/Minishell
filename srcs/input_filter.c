
#include "../includes/minishell.h"

char	*input_space_filter(char *input, int len)
{
	int		s;
	int		e;
	int		idx;
	char	*new_input;

	new_input = (char *)malloc(sizeof(char) * len);
	ft_bzero(new_input, len);
	if (!new_input)
		return (new_input);
	s = 0;
	idx = 0;
	while (input[s])
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