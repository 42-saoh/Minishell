/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_out_dup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 20:44:43 by taekang           #+#    #+#             */
/*   Updated: 2021/09/01 20:09:06 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	file_open_getfd_out(char *content, int e, int is_append)
{
	char	*file_nm;
	int		fd;

	file_nm = get_right_str(content, e);
	if (!file_nm)
		return (0);
	if (is_append)
		fd = open(file_nm, O_WRONLY | O_CREAT | O_APPEND, \
					S_IRUSR | S_IWUSR);
	else
		fd = open(file_nm, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, \
							S_IRUSR | S_IWUSR);
	ft_free(file_nm);
	if (fd == -1)
		stderr_print(SHELL_NAME, file_nm, NO_SUCH_FILE);
	return (fd);
}

int	set_right_fd_out(char *content, int i, int fds[2], int is_append)
{
	char	*num;

	if (content[i] == '&')
		fds[1] = get_ampersand_fd(content, i);
	else
	{
		fds[1] = file_open_getfd_out(content, i, is_append);
		if (fds[1] <= 0)
			return (0);
	}
	if (fds[1] > FD_MAX)
	{
		num = ft_itoa(fds[1]);
		if (!num)
			return (0);
		return (stderr_print(SHELL_NAME, num, BAD_FD));
	}
	return (1);
}

int	redirect_out_dup(int fds[2], char *content)
{
	int	i;
	int	is_append;

	i = 0;
	is_append = 0;
	if (content[i] == REDIRECT_OUT)
	{
		is_append = 1;
		i++;
	}
	if (!set_right_fd_out(content, i, fds, is_append))
		return (0);
	redirection_dup_exec(fds);
	return (1);
}
