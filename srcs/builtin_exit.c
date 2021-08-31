#include "../includes/minishell.h"

long	ft_atoi_long_exit(char *str, int *flag)
{
	unsigned long long	get_num;
	long				result;
	int					i;

	i = 0;
	get_num = 0;
	result = 1;
	if (str[i] == '-')
		result = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && str[i] >= '0' && str [i] <= '9')
	{
		get_num = (get_num * 10) + (str[i] - '0');
		if (get_num > 9223372036854775808U)
			*flag = 1;
		else if (get_num > 1844674407370955161 && str[i + 1] != 0)
			*flag = 1;
		i++;
	}
	if (str[i] != 0)
		*flag = 1;
	result = result * get_num;
	return (result);
}

void	error_exit(char *str)
{
	printf("%s", str);
	exit(255);
}

void	builtin_exit(t_info *info)
{
	int		argc;
	int		error_flag;
	long	exit_num;

	argc = get_argc(info->param);
	error_flag = 0;
	if (argc == 1)
		exit(0);
	else if (argc == 2)
	{
		exit_num = ft_atoi_long_exit(info->param[1], &error_flag);
		if (exit_num == EXEC_FAIL)
			exit(1);
		if (error_flag)
			error_exit("exit: -n: numeric argument required\n");
		exit (exit_num);
	}
	else
	{
		exit_num = ft_atoi_long_exit(info->param[1], &error_flag);
		if (error_flag)
			error_exit("exit: -n: numeric argument required\n");
		printf("exit \nexit: too many arguments\n");
		exit(EXEC_FAIL);
	}
}
