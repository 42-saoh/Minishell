/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 19:03:01 by taesan            #+#    #+#             */
/*   Updated: 2021/08/31 20:22:51 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	no_such_file_error(char *file_nm)
{
	write(STDERR_FILENO, TEMP_FILE, ft_strlen(TEMP_FILE));
	write(STDERR_FILENO, ": ", 3);
	perror(NO_SUCH_FILE);
}

int	stderr_print(char *cmd, char *param, char *msg)
{
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": ", 3);
	write(STDERR_FILENO, param, ft_strlen(param));
	write(STDERR_FILENO, ": ", 3);
	perror(msg);
	return (0);
}

int	error_occur_perror(char *msg)
{
	perror(msg);
	return (0);
}