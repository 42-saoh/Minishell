/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 21:17:51 by taesan            #+#    #+#             */
/*   Updated: 2021/08/14 00:09:04 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		remove_redirect(int s, int e, char **content)
{
	char *left;
	char *right;
	char *new_input;

	new_input = 0;
	left = ft_substr(*content, 0, s);
	if (left)
	{
		right = ft_substr(*content + e, 0, ft_strlen(*content) - e);
		if (right)
		{
			new_input = ft_strjoin(left, right);
			ft_free(right);
		}
		ft_free(left);
	}
	if (!new_input)
		return (0);
	ft_free(*content);
	*content = new_input;
	return (1);
}