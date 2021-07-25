/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 19:03:01 by taesan            #+#    #+#             */
/*   Updated: 2021/06/30 19:03:01 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	error_occur_perror(char *msg)
{
	perror(msg);
	return (0);
}

int	error_occur_std(char *msg)
{
	ft_putendl_fd(msg, 1);
	return (0);
}
