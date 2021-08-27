#include "../includes/minishell.h"

void	builtin_pwd(t_info *info)
{
	char *path;
	int	argc;

	argc = get_argc(info->param);
	if (argc != 1)
	{
		printf("pwd: too many arguments\n");
		exit(EXEC_FAIL);
	}
	path = getcwd(NULL, BUFSIZ);
	printf("%s\n", path);
	exit(0);
}
