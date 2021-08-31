/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_connect_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 16:03:38 by taesan            #+#    #+#             */
/*   Updated: 2021/08/13 16:46:25 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_connect_pipe(t_info *info, int seq)
{
	if (seq > 0)
	{
		info->pipe_in[0] = info->pipe_out[0];
		if (pipe(info->pipe_out) == -1)
			return (error_occur_perror(PIPE_ERR));
	}
	info->connect_pipe[0] = info->pipe_in[0];
	info->connect_pipe[1] = info->pipe_out[1];
	return (1);
}
