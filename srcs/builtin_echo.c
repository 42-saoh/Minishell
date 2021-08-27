#include "../includes/minishell.h"

void	builtin_echo(t_info *info)
{
	int	i;
	int	n_flag;
	int	argc;

	i = 1;
	n_flag = 0;
	if (info->param[1][0] == '-')
	{
		if (info->param[1][1] == 'n')
			n_flag++;
		i++;
	}
	argc = get_argc(info->param);
	while (i < argc)
	{
		if (i == argc - 1)
			printf("%s", info->param[i]);
		else
			printf("%s ", info->param[i]);
		i++;
	}
	if (!n_flag)
		printf("\n");
	exit(0);
}
