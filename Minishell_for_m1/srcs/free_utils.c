/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 20:46:35 by taesan            #+#    #+#             */
/*   Updated: 2021/09/01 17:22:43 by taekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	content_not_rm(void *param)
{
	void	*temp;

	temp = param;
	return ;
}

void	remove_file(void)
{
	struct stat	sb;

	if (stat(ENV_FILE, &sb) == 0 && unlink(ENV_FILE) == -1)
		write(STDERR_FILENO, UNLINK_ERR, ft_strlen(UNLINK_ERR));
	if (stat(EXPORT_FILE, &sb) == 0 && unlink(EXPORT_FILE) == -1)
		write(STDERR_FILENO, UNLINK_ERR, ft_strlen(UNLINK_ERR));
}
