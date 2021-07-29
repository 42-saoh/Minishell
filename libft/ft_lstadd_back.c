/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saoh <saoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 15:00:29 by saoh              #+#    #+#             */
/*   Updated: 2021/02/16 18:44:53 by saoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstadd_back(t_list **lst, t_list *newlst)
{
	t_list	*curr;

	if (newlst == NULL)
		return ;
	if (*lst == NULL)
		*lst = newlst;
	else
	{
		curr = *lst;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = newlst;
	}
}
