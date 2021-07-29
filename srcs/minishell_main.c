#include "minishell.h"

void	init_minishell(char **envp, t_minishell *ms)
{
	ms->envp = envp;
	ms->cmdlst = cmdlst_new();
	ms->cmdlst_head = ms->cmdlst;
}

void	free_all(t_minishell *ms)
{
	printf("%s\n", ms->envp[0]);
	free_cmdlst(ms->cmdlst_head);
}

int main(int argc, char **argv, char **envp)
{
	t_minishell	ms;

	if (argc != 1)
		return (0);
	if (argv == NULL)
		return (0);
	init_minishell(envp, &ms);
	minishell_roop(&ms);
	free_all(&ms);
}
