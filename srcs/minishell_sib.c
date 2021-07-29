#include "minishell.h"

void	start_sibling_process(t_minishell *ms)
{
	printf("sibling : %d\n", ms->sib_pid);
	sleep(1);
	exit(0);
}
