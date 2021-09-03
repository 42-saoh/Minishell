/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_macro.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:19:49 by taesan            #+#    #+#             */
/*   Updated: 2021/09/03 15:44:24 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit_status(int status)
{
	return ((status >> 8) & 0x000000ff);
}

int	term_status(int status)
{
	return (status & 0177);
}
