/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 10:47:44 by taesan            #+#    #+#             */
/*   Updated: 2021/08/22 02:20:40 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*append_content(char *buf, char *content)
{
	char	*new_c;
	int		i;
	int		j;

	if (!content)
		return (content_null(buf));
	new_c = (char *)malloc(ft_strlen(buf) + ft_strlen(content) + 1);
	if (!new_c)
		return (0);
	i = 0;
	while (content[i])
	{
		new_c[i] = content[i];
		i++;
	}
	j = 0;
	while (buf[j])
	{
		new_c[i + j] = buf[j];
		j++;
	}
	new_c[i + j] = 0;
	free(content);
	return (new_c);
}

char	*create_new(char *content, char *result, int idx)
{
	int		i;
	int		len;
	char	*new_content;

	len = ft_strlen(content) - idx + 2;
	new_content = (char *)malloc(sizeof(char) * len);
	if (!new_content)
	{
		free(result);
		return (0);
	}
	i = 0;
	while (i < len - 1)
		new_content[i++] = content[idx++];
	new_content[len - 1] = 0;
	return (new_content);
}

int	line_check(int fd, char **contents, char **line, int is_finish)
{
	int		i;
	char	*new_content;
	char	*result;

	i = 0;
	while (contents[fd][i])
	{
		if (contents[fd][i] == '\n')
		{
			result = ft_substr(contents[fd], 0, i);
			new_content = create_new(contents[fd], result, i + 1);
			if (!result || !new_content)
				return (-1);
			free(contents[fd]);
			contents[fd] = new_content;
			*line = result;
			return (1);
		}
		i++;
	}
	*line = ft_strdup(contents[fd]);
	if (is_finish && !(*line))
		return (-1);
	return (0);
}

int	finish(int fd, char **contents, char **line, int read_r)
{
	int	line_exist;

	if (read_r == -1)
		return (-1);
	line_exist = 0;
	if (contents[fd])
		line_exist = line_check(fd, contents, line, 1);
	if (line_exist)
		return (line_exist);
	if (contents[fd])
	{
		free(contents[fd]);
		contents[fd] = 0;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*contents[FOPEN_MAX];
	char		*buf;
	int			read_r;
	int			line_exist;

	buf = check_first(fd, line);
	if (!buf)
		return (-1);
	read_r = read(fd, buf, BUFFER_SIZE);
	while (read_r > 0)
	{
		buf[read_r] = 0;
		contents[fd] = append_content(buf, contents[fd]);
		if (!contents[fd])
			return (-1);
		line_exist = line_check(fd, contents, line, 0);
		if (line_exist != 0)
		{
			free(buf);
			return (line_exist);
		}
		read_r = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	return (finish(fd, contents, line, read_r));
}
