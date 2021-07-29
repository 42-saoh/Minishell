#include "minishell.h"

static void	put_char(char *str, int c)
{
	while (*str)
		str++;
	*str = (char)c;
}

static int	search_and_put_envp(char *envp, char *line, int line_len, char *str)
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
	{
		while (envp[++i])
			put_char(str ,envp[i]);
		return (1);
	}
	return (0);
}

static char	*put_envp(char **envp, char *line, char *str)
{
	int	line_len;

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
		if (search_and_put_envp(*envp, line, line_len - 1, str))
		{
			line += (line_len - 1);
			return (line);
		}
		envp++;
	}
	line += (line_len - 1);
	return (line);
}

static char	*put_sg_quotes(char *line, char *str)
{
	char	*test_line;

	line++;
	test_line = line;
	while (*test_line != 39 && *test_line)
		test_line++;
	if (!(*test_line))
	{
		put_char(str, 39);
		return (line);
	}
	while (*line != 39)
	{
		put_char(str, *line);
		line++;
	}
	line++;
	return (line);
}

static char	*put_db_quotes(t_minishell *ms, char *line, char *str)
{
	char	*test_line;

	line++;
	test_line = line;
	while (*test_line != 34 && *test_line)
		test_line++;
	if (!(*test_line))
	{
		put_char(str, 34);
		return (line);
	}
	while (*line != 34)
	{
		if (*line == '$')
		{
			line = put_envp(ms->envp, line, str);
			continue ;
		}
		put_char(str, *line);
		line++;
	}
	line++;
	return (line);
}

char	*put_str(t_minishell *ms, char *line, char *str)
{
	while (*line == ' ')
		line++;
	while (*line != ' ' && *line)
	{
		if (*line == 34)
			line = put_db_quotes(ms, line, str);
		else if (*line == 39)
			line = put_sg_quotes(line, str);
		else if (*line == '$')
			line = put_envp(ms->envp, line, str);
		else if (*line == '|')
			break ;
		else
		{
			put_char(str, *line);
			line++;
		}
	}
	return (line);
}
