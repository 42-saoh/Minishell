#include "../includes/minishell.h"

int	here_doc_exec(char *limiter, int fds[2], int fd_in)
{
	char	*buf;
	int		r;
	int		fd;

	fd = open(TEMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return (error_occur_perror(INPUT_OPEN_ERR));
	r = get_next_line(fd_in, &buf);
	while (r > 0)
	{
		if (ft_strcmp(buf, limiter) == 0)
			break ;
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		r = get_next_line(fd_in, &buf);
	}
	if (buf)
		ft_free(buf);
	ft_close(fd);
	fds[1] = open(TEMP_FILE, O_RDONLY, S_IRUSR | S_IWUSR);
	if (fds[1] == -1)
		printf("%s: %s\n", TEMP_FILE, NO_SUCH_FILE);
	return (fds[1]);
}

int	file_open_getfd_in(char *content, int e)
{
	char	*file_nm;
	int		fd;

	file_nm = get_right_str(content, e);
	if (!file_nm)
		return (0);
	fd = open(file_nm, O_RDONLY);
	if (fd == -1)
		printf("%s: %s\n", file_nm, NO_SUCH_FILE);
	ft_free(file_nm);
	return (fd);
}

int	set_right_fd_in(char *content, int i, int fds[2])
{
	if (content[i] == '&')
		fds[1] = get_ampersand_fd(content, i, fds);
	else
	{
		fds[1] = file_open_getfd_in(content, i);
		if (fds[1] <= 0)
			return (0);
	}
	return (1);
}

int	redirect_in_dup(t_info *info, int std_in, char *content)
{
	int		i;
	char	*limiter;

	i = 0;
	if (content[i] == REDIRECT_IN)
	{
		i++;
		limiter = get_right_str(content, i);
		if (!limiter)
			return (0);
		if (here_doc_exec(limiter, info->redirect_fd, std_in) <= 0)
		{
			free(limiter);
			return (0);
		}
		free(limiter);
	}
	else
		if (!set_right_fd_in(content, i, info->redirect_fd))
			return (0);
	redirection_dup_exec(info->redirect_fd);
	return (1);
}
