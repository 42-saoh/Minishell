#include "../includes/minishell.h"

int	find_root(char *envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	if (i < 4)
		return (0);
	else if (envp[0] == 'H' && envp[1] == 'O' && envp[2] == 'M' && envp[3] == 'E'
			&& envp[4] == '=')
		return (1);
	else
		return (0);
}

void	get_root_dir(char **envp)
{
	char *a;
	int	i;

	while (*envp)
	{
		if (find_root(*envp))
			break ;
		envp++;
	}
	if (!(*envp))
	{
		printf("Home is not finded\n");
		exit(EXEC_FAIL);
	}
	a = ft_strdup(*envp + 5);
	i = chdir(a);
	free(a);
	if (i)
	{
		printf("does not exist path\n");
		exit(EXEC_FAIL);
	}
}

void	builtin_cd(int argc, char **argv, char **envp)
{
	int i;

	if (argc == 1)
		get_root_dir(envp);
	else if (argc > 2)
	{
		printf("too many arguments\n");
		exit(EXEC_FAIL);
	}
	else
	{
		i = chdir(argv[1]);
		if (i)
		{
			printf("does not exist path\n");
			exit(EXEC_FAIL);
		}
	}
	exit(0);
}
