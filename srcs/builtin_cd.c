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
		printf("ERROR\n");
		exit(-1);
	}
	a = ft_strdup(*envp + 5);
	i = chdir(a);
	printf("%d\n", i);
	free(a);
	a = getcwd(NULL, BUFSIZ);
	printf("%s\n", a);
	free(a);
}

void	builtin_cd(int argc, char **argv, char **envp)
{
	int i;
	char *path;

	if (argc == 1)
		get_root_dir(envp);
	else if (argc > 2)
	{
		printf("error\n");
		return ;
	}
	else
	{
		i = chdir(argv[1]);
		printf("i : %d argc : %d\n", i, argc);
		printf("%s\n", strerror(errno));
		path = getcwd(NULL, BUFSIZ);
		printf("%s\n", path);
	}
}
