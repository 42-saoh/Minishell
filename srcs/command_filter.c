#include "../includes/minishell.h"

int	quote_filter(t_info *info, char **input, int s, int *e)
{
	int		dollar_idx;
	char	is_db_q;

	is_db_q = (*input)[s];
	if (is_db_q == DOUBLE_Q)
	{
		dollar_idx = exist_dollar(*input, s, *e);
		if (dollar_idx)
		{
			if (!replace_env(info->envp, input, dollar_idx, e))
				return (0);
		}
	}
	return (1);
}

int	filter_input(t_info *info, char **input, int len)
{
	int		s;
	int		e;

	e = 0;
	while (e < len && (*input)[e])
	{
		if (is_quotation((*input)[e]))
		{
			s = e++;
			while ((*input)[e] && (*input)[e] != (*input)[s])
				e++;
			if (e < len && (*input)[s] == (*input)[e] && \
				!quote_filter(info, input, s, &e))
				return (0);
		}
		else if ((*input)[e] == DOLLAR)
		{
			if (!replace_env(info->envp, input, e, &e))
				return (0);
			len = ft_strlen(*input);
		}
		e++;
	}
	return (1);
}

int	command_filter(t_info *info, char **content)
{
	char	**temp;
	int		len;
	int		r;

	len = ft_strlen((char *)(*content));
	if (!filter_input(info, content, len))
		return (error_occur_perror(FILTER_INPUT_ERR));
	len = ft_strlen((char *)(*content));
	r = make_param(info, *content, len);
	if (info->param[1])
		r = filter_asterisk(info, 1);
	if (info->asterisk_check && info->envp_cnt > 2)
	{
		temp = (char **)malloc(sizeof(char *) * (info->param_cnt + 1));
		if (temp)
		{
			merge_sort(info->param, temp, 1, info->param_cnt - 1);
			ft_free(temp);
		}
		else
			r = 0;
	}
	ft_lstclear(&info->param_list, content_not_rm);
	ft_lstclear(&info->temp_list, ft_free);
	return (r);
}
