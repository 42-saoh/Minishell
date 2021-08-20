#include "../includes/minishell.h"

void	builtin_echo(int argc, char **argv, char **envp)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (argv[1][0] == '-')
	{
		if (argv[1][1] == 'n')
			n_flag++;
		i++;
	}
	while (i < argc)
	{
		if (i == argc - 1)
			printf("%s", argv[i]);
		else
			printf("%s ", argv[i]);
		i++;
	}
	if (!n_flag)
		printf("\n");
	exit(0);
}
