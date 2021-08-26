#include "../includes/minishell.h"

// int	write_export_substr(t_info *info, char *param, int j)
// {
// 	char	*key;
// 	char	*value;
// 	int		r;

//  	key = ft_substr(param, 0, j);
// 	value = ft_substr(param + j + 1, 0, ft_strlen(param) - j);
// 	r = 1;
// 	if (key && value)
// 	{
// 		if (is_empty(key))
// 			export_errror(param);
// 		else
// 			r = write_env_file(info, key, value);
// 		if (r)
// 			r = write_export_file(key, 1);
// 	}
// 	ft_free(key);
// 	ft_free(value);
// 	if ((key && !value) || (!key && value))
// 		return (0);
// 	return (r);
// }

int	check_and_write_exec(char *param)
{
	int 	i;
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
	int		j;
	char	*param;

	i = 1;
	while (info->param[i])
	{
		// param = info->param[i];
		// j = 0;
		// while (param[j] && param[j] != '=')
		// 	j++;
		// if (param[j] == '=')
		// 	r = write_export_substr(info, param, j);
		// else if (is_empty(param))
		// 	export_errror(param);
		// else
		// 	r = write_export_file(param, 0);
		// i++;
		if (!check_and_write_exec(info->param[i]))
			exit(EXEC_FAIL);
		i++;
	}
	exit(0);
}