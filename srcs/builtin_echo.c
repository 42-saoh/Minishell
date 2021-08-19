#include "../includes/minishell.h"

void	builtin_echo(int argc, char **argv, char **envp)
{
	int	i;
	int	len;

	i = 1;
	len = 1;
	while (argv[len])
		len++;
	while (i < len)
	{
		if (i == len - 1)
			printf("%s", argv[i]);
		else
			printf("%s ", argv[i]);
		i++;
	}
	printf("\n");
}
