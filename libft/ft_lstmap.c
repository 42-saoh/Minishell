/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saoh <saoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 15:49:12 by saoh              #+#    #+#             */
/*   Updated: 2020/10/24 13:41:16 by saoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*n_lst;
	t_list	*temp;

	if (lst == NULL || f == NULL)
	{
		n_lst = 0;
		return (n_lst);
	}
	n_lst = NULL;
	while (lst != NULL)
	{
		if (!(temp = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&n_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&n_lst, temp);
		lst = lst->next;
	}
	return (n_lst);
}
