#include "../includes/minishell.h"

void	builtin_pwd(int argc, char **argv, char **envp)
{
	char *path;

	if (argc != 1)
	{
		printf("pwd: too many arguments\n");
		return ;
	}
	path = getcwd(NULL, BUFSIZ);
	printf("%s\n", path);
}
