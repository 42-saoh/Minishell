#include "minishell.h"

int	get_readline(t_minishell *ms)
{
	ms->read_line = readline("my minishell : ");
	rlst_add(ms->rlst, ms->read_line);
	add_history(ms->read_line);
	return (0);
}

void	parsing_line(t_minishell *ms)
{
	int	len;
	char	*str;

	len = get_str_len(ms, ms->read_line);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
	{
		printf("M ERROR\n");
		return ;
	}
	ft_memset(str, 0, len + 1);
	ms->read_line = put_str(ms, ms->read_line, str);
	printf("%s\n", str);
	free(str);
}

void	minishell_roop(t_minishell *ms)
{
	while(1)
	{
		get_readline(ms);
		parsing_line(ms);
		ms->sib_pid = fork();
		if (ms->sib_pid == 0)
			start_sibling_process(ms);
		wait(&ms->sib_p_state);
	}
}

/*
 *
	while (*ms->read_line)
	{
		if (ms->read_line == 66)
			parsing_db_quotes(ms);
		else if (ms->read_line == 71)
			parsing_sg_quotes(ms);
		parsing_str(ms);
		while (*ms->read_line == ' ')
			ms->read_line++;
	}
*/
