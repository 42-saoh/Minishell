#include "minishell.h"

void	set_lst(t_minishell *ms)
{
	free_cmdlst(ms->cmdlst_head);
	ms->cmdlst = cmdlst_new();
	ms->cmdlst_head = ms->cmdlst;
}

int	get_readline(t_minishell *ms)
{
	ms->read_line = readline("my minishell : ");
	add_history(ms->read_line);
	return (0);
}

void	parsing_line(t_minishell *ms)
{
	int	len;
	char	*str;

	while (*ms->read_line)
	{
		len = get_str_len(ms, ms->read_line);
		if (len == 0)
			break ;
		str = (char *)malloc(sizeof(char) * len + 1);
		if (!str)
		{
			printf("M ERROR\n");
			return ;
		}
		ft_memset(str, 0, len + 1);
		ms->read_line = put_str(ms, ms->read_line, str);
		cmdlst_add(ms->cmdlst, (void *)str);
	}
	while (ms->cmdlst)
	{
		printf("%s\n", (char *)ms->cmdlst->content);
		ms->cmdlst = ms->cmdlst->next;
	}
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
		set_lst(ms);
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
