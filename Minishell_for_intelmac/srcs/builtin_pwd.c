/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekang <taekang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 16:41:21 by taekang           #+#    #+#             */
/*   Updated: 2021/09/06 16:41:22 by taekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
				stderr_print("pwd", info->param[1], "invalid option");
				exit(1);
			}
		}
	}
	path = getcwd(NULL, BUFSIZ);
	printf("%s\n", path);
	exit(0);
}
