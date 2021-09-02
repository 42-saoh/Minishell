/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 19:03:01 by taesan            #+#    #+#             */
/*   Updated: 2021/09/02 20:31:06 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	export_errror(char *param)
{
	write(STDERR_FILENO, SHELL_NAME, ft_strlen(SHELL_NAME));
	write(STDERR_FILENO, ": ", 3);
	write(STDERR_FILENO, "export: `", 10);
	ft_putstr_fd(param, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (0);
}