/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_command_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekang <taekang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 16:40:31 by taekang           #+#    #+#             */
/*   Updated: 2021/09/06 16:40:33 by taekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	move_end_point(char *line, int *e, char end_c)
{
	int	idx;

	idx = *e + 1;
	while (line[idx] && line[idx] != end_c)
		idx++;
	if (!line[idx])
		return (error_occur_perror(NOT_CLOSED));
	*e = idx;
	return (1);
}

int	init_default(t_info *info, char *input, int *s, int *e)
{
	info->command_cnt = 0;
	info->is_builtin = -1;
	if (pipe(info->pipe_out) == -1)
		return (error_occur_perror(PIPE_ERR));
	info->std_in = dup(STDIN_FILENO);
	if (info->std_in == -1)
		return (error_occur_perror("dup"));
	info->input = input;
	*s = 0;
	*e = 0;
	return (1);
}

int	make_command_list(t_info *info, char *input)
{
	int	s;
	int	e;
	int	len;

	len = ft_strlen(input);
	init_default(info, input, &s, &e);
	while (e < len && input[e])
	{
		if (is_quotation(input[e]) && !move_end_point(input, &e, input[e]))
			return (2);
		else if (input[e] == PIPE)
		{
			if (!append_pipe_command(info, input, &s, &e))
				return (0);
		}
		else if (input[e] == '&')
		{
			if (!append_amper_command(info, input, &s, &e))
				return (0);
		}
		e++;
	}
	if (!append_command(info, input, s, e))
		return (0);
	return (1);
}
