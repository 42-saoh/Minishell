#include "../includes/minishell.h"

int	get_argc(char **argv)
{
	int	i;

	i = 0;
	while (*argv)
	{
		argv++;
		i++;
	}
	return (i);
}

void	builtin_pwd(t_info *info)
{
	char	*path;
	int		argc;

	argc = get_argc(info->param);
	if (argc > 1)
	{
		if (info->param[1][0] == '-')
		{
			if (info->param[1][1] != 0 && (info->param[1][1] != '-' ||
						info->param[1][2] != 0))
			{
				printf("pwd: %s: invalid option\n", info->param[1]);
				exit(EXEC_FAIL);
			}
		}
	}
	path = getcwd(NULL, BUFSIZ);
	printf("%s\n", path);
	exit(0);
}
