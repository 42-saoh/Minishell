/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 19:03:01 by taesan            #+#    #+#             */
/*   Updated: 2021/09/01 17:14:27 by taekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	no_such_file_error(char *file_nm)
{
	write(STDERR_FILENO, file_nm, ft_strlen(file_nm));
	write(STDERR_FILENO, ": ", 3);
	write(STDERR_FILENO, NO_SUCH_FILE, ft_strlen(NO_SUCH_FILE));
	write(STDERR_FILENO, "\n", 2);
}

int	error_occur_perror(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 2);
	return (0);
}

int	stderr_print(char *cmd, char *param, char *msg)
{
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": ", 3);
	write(STDERR_FILENO, param, ft_strlen(param));
	write(STDERR_FILENO, ": ", 3);
	error_occur_perror(msg);
	return (0);
}
