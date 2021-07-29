#include "minishell.h"

static int	search_envp(char *envp, char *line, int line_len)
{
	int	i;

	i = 0;
	while (i < line_len)
	{
		if (line[i] != envp[i])
			break ;
		i++;
	}
	if (i == line_len && envp[i] == '=')
		return ((int)ft_strlen(envp) - (i + 1));
	return (0);
}

static char	*get_envp(char **envp, char *line, int *str_len)
{
	int	line_len;
	int	p_str_len;

	line_len = 1;
	while (line[line_len])
	{
		if (line[line_len] == ' ' || line[line_len] == 39 ||
				line[line_len] == 34 || line[line_len] == '$')
			break ;
		line_len++;
	}
	line++;
	while (*envp)
	{
		p_str_len = search_envp(*envp, line, line_len - 1);
		if (p_str_len)
		{
			*str_len += p_str_len;
			line += (line_len - 1);
			return (line);
		}
		envp++;
	}
	line += (line_len - 1);
	return (line);
}

static char	*get_sg_quotes(char *line, int *str_len)
{
	char	*test_line;

	line++;
	test_line = line;
	while (*test_line != 39 && *test_line && *test_line != 124)
		test_line++;
	if (*test_line == 0 || *test_line == 124)
	{
		(*str_len)++;
		return (line);
	}
	while (*line != 39)
	{
		line++;
		(*str_len)++;
	}
	line++;
	return (line);
}

static char	*get_db_quotes(t_minishell *ms, char *line, int *str_len)
{
	char	*test_line;

	line++;
	test_line = line;
	while (*test_line != 34 && *test_line && *test_line != 124)
		test_line++;
	if (*test_line == 0 || *test_line == 124)
	{
		(*str_len)++;
		return (line);
	}
	while (*line != 34 && *line)
	{
		if (*line == '$')
		{
			line = get_envp(ms->envp, line, str_len);
			continue ;
		}
		line++;
		(*str_len)++;
	}
	line++;
	return (line);
}

int	get_str_len(t_minishell *ms, char *line)
{
	int	str_len;

	str_len = 0;
	while (*line == ' ')
		line++;
	while (*line != ' ' && *line)
	{
		if (*line == 34)
			line = get_db_quotes(ms, line, &str_len);
		else if (*line == 39)
			line = get_sg_quotes(line, &str_len);
		else if (*line == '$')
			line = get_envp(ms->envp, line, &str_len);
		else
		{
			line++;
			str_len++;
		}
	}
	return (str_len);
}
