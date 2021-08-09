/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   using_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:56:59 by taesan            #+#    #+#             */
/*   Updated: 2021/08/08 17:24:22 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirect_out_free(void *data)
{
	t_redirect_out *temp;

	temp = (t_redirect_out *)(data);
	ft_close(temp->left_fd);
	ft_close(temp->right_fd);
	ft_free(temp);
}

void	redirect_in_free(void *data)
{
	t_redirect_in *temp;

	temp = (t_redirect_in *)(data);
	if (temp->limiter)
		ft_free(temp->limiter);
	ft_close(temp->left_fd);
	ft_close(temp->right_fd);
	ft_free(temp);
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