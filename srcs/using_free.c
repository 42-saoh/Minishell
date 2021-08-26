/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   using_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:56:59 by taesan            #+#    #+#             */
/*   Updated: 2021/08/26 02:48:35 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	info->param_list비우는 용도.
*/
void content_not_rm(void *param)
{
	return ;
}

void	ft_free(void *data)
{
	if (!data)
		return ;
	free(data);
	data = 0;
}

void	split_free(char **data)
{
	int	i;

	if (!data || !*data)
		return ;
	i = 0;
	while (data[i])
		ft_free(data[i++]);
	free(data);
	data = 0;
}

void	clear_data(t_info *info)
{
	if (info->commands)
		ft_lstclear(&info->commands, ft_free);
	if (info->redirect_lst)
		ft_lstclear(&info->redirect_lst, ft_free);
	if (info->commands_symbol)
		ft_lstclear(&info->commands_symbol, ft_free);
	ft_close(info->std_in);
}

void	remove_file()
{
	struct stat sb;

	if (stat(ENV_FILE, &sb) == 0 && unlink(ENV_FILE) == -1)
		printf("[file_nm : %s] %s\n",ENV_FILE, UNLINK_ERR);
	if (stat(EXPORT_FILE, &sb) == 0 && unlink(EXPORT_FILE) == -1)
		printf("[file_nm : %s] %s\n",EXPORT_FILE, UNLINK_ERR);
}

void	clear_all_data(t_info *info)
{
	char	**temp;

	if (info->paths)
	{
		temp = info->paths;
		while (*temp)
		{
			ft_free(*temp);
			temp++;
		}
	}
	if (info->envp)
	{
		temp = info->envp;
		while (*temp)
		{
			ft_free(*temp);
			temp++;
		}
	}
	clear_data(info);
	remove_file();
}