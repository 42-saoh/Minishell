#include "../includes/minishell.h"

int	move_db_redirect_out(char *content, int *e)
{
	int	idx;

	idx = *e + 2;
	if (!content[idx])
		return (0);
	else if (content[idx] == REDIRECT_IN || content[idx] == REDIRECT_OUT)
		return (0);
	else if (content[idx] == '&')
		return (move_redirect_and(content, e, idx));
	else if (content[idx] == ' ')
		return (move_redirect_space(content, e, idx));
	else
	{
		while (content[idx] && content[idx] != ' ')
		{
			if (content[idx] == SINGLE_Q || content[idx] == DOUBLE_Q)
				move_quot_point(content, &idx, content[idx]);
			else
				idx++;
		}
		*e = idx;
	}
	return (1);
}

int	move_db_redirect_in(char *content, int *e)
{
	int	idx;

	idx = *e + 2;
	if (!content[idx])
		return (0);
	else if (content[idx] == REDIRECT_IN || content[idx] == REDIRECT_OUT)
		return (0);
	else if (content[idx] == '&')
		return (0);
	else if (content[idx] == ' ')
		return (move_redirect_space(content, e, idx));
	else
	{
		while (content[idx] && content[idx] != ' ')
		{
			if (content[idx] == SINGLE_Q || content[idx] == DOUBLE_Q)
				move_quot_point(content, &idx, content[idx]);
			else
				idx++;
		}
		*e = idx;
	}
	return (1);
}

int	move_sg_redirect_in(char *content, int *e)
{
	int	idx;

	idx = *e + 1;
	if (!content[idx])
		return (0);
	else if (content[idx] == REDIRECT_OUT)
		return (0);
	else if (content[idx] == '&')
		return (move_redirect_and(content, e, idx));
	else if (content[idx] == ' ')
		return (move_redirect_space(content, e, idx));
	else
	{
		while (content[idx] && content[idx] != ' ')
		{
			if (content[idx] == SINGLE_Q || content[idx] == DOUBLE_Q)
				move_quot_point(content, &idx, content[idx]);
			else
				idx++;
		}
		*e = idx;
	}
	return (1);
}

int	move_sg_redirect_out(char *content, int *e)
{
	int	idx;

	idx = *e + 1;
	if (!content[idx])
		return (0);
	else if (content[idx] == REDIRECT_IN)
		return (0);
	else if (content[idx] == '&')
		return (move_redirect_and(content, e, idx));
	else if (content[idx] == ' ')
		return (move_redirect_space(content, e, idx));
	else
	{
		while (content[idx] && content[idx] != ' ')
		{
			if (content[idx] == SINGLE_Q || content[idx] == DOUBLE_Q)
				move_quot_point(content, &idx, content[idx]);
			else
				idx++;
		}
		*e = idx;
	}
	return (1);
}

int	redirect_get_end(char *content, int *e)
{
	int	i;

	if (content[*e] == REDIRECT_IN && content[*e + 1] == REDIRECT_IN)
		i = move_db_redirect_in(content, e);
	else if (content[*e] == REDIRECT_OUT && content[*e + 1] == REDIRECT_OUT)
		i = move_db_redirect_out(content, e);
	else if (content[*e] == REDIRECT_IN)
		i = move_sg_redirect_in(content, e);
	else if (content[*e] == REDIRECT_OUT)
		i = move_sg_redirect_out(content, e);
	else
		i = 0;
	return (i);
}
