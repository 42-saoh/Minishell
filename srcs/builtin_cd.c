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

void	get_root_dir_sib(char **envp)
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
	if (i)
	{
		printf("cd: %s: %s\n", a, strerror(errno));
		free(a);
		exit(EXEC_FAIL);
	}
	free(a);
}

void	builtin_cd_sib(t_info *info)
{
	int i;

	i = get_argc(info->param);
	if (i == 1)
		get_root_dir_sib(info->envp);
	else
	{
		i = chdir(info->param[1]);
		if (i)
		{
			printf("cd: %s: %s\n", info->param[1], strerror(errno));
			exit(EXEC_FAIL);
		}
	}
	exit(0);
}

void	get_root_dir_parent(char **envp)
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
		return ;
	a = ft_strdup(*envp + 5);
	i = chdir(a);
	free(a);
}

void	builtin_cd_parent(t_info *info)
{
	int i;

	i = get_argc(info->param);
	if (i == 1)
		get_root_dir_parent(info->envp);
	else
		i = chdir(info->param[1]);
}
