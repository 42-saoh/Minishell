/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saoh <saoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 21:53:06 by saoh              #+#    #+#             */
/*   Updated: 2021/07/26 12:40:26 by saoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list			*rlst_new(void)
{
	t_list		*new_lst;

	new_lst = (t_list *)malloc(sizeof(t_list));
	new_lst->content = NULL;
	new_lst->next = NULL;
	return (new_lst);
}

void			rlst_add(t_list *lst, void *content)
{
	if (lst->content)
	{
		while (lst->next)
			lst = lst->next;
		lst->next = rlst_new();
		lst = lst->next;
	}
	lst->content = content;
}

void			free_rlst(t_list *lst)
{
	if (lst->next != NULL)
		free_rlst(lst->next);
	if (lst->content != NULL)
		free(lst->content);
	free(lst);
}
