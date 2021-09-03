/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   using_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:56:59 by taesan            #+#    #+#             */
/*   Updated: 2021/09/03 20:07:05 by taekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	paths_clear(t_info *info)
{
	int	i;

	i = 0;
	if (info->paths)
	{
		while (info->paths[i])
		{
			ft_free(info->paths[i]);
			i++;
		}
		ft_free(info->paths);
	}
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

void	clear_all_data(t_info *info)
{
	paths_clear(info);
	clear_envp_info(info);
	clear_data(info);
	remove_file();
}
