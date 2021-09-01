#include "../includes/minishell.h"

int	check_and_write_exec(char *param)
{
	int		i;
	int		r;
	char	*key;

	i = 0;
	key = 0;
	r = 1;
	while (param[i] && param[i] != '=')
		i++;
	if (param[i] == '=')
	{
		key = ft_substr(param, 0, i);
		if (!key)
			return (0);
		if (is_empty(key))
			export_errror(param);
		else
			r = write_env_file(key, param);
		ft_free(key);
	}
	else if (is_empty(param))
		export_errror(param);
	else
		return (write_export_file(param));
	return (r);
}

void	export_add_var(t_info *info)
{
	int		i;

	i = 1;
	while (info->param[i])
	{
		if (!check_and_write_exec(info->param[i]))
			exit(EXEC_FAIL);
		i++;
	}
	exit(0);
}
