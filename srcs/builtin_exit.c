#include "../includes/minishell.h"

void	builtin_exit(int argc, char **argv, char **envp)
{
	int i;
	char **a;
	char **b;

	exit(0);
	a = argv;
	b = envp;
	i = argc;
}
