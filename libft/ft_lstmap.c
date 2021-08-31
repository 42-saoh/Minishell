/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekang <taekang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 18:57:44 by taekang           #+#    #+#             */
/*   Updated: 2021/08/31 15:57:47 by taekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*append;

	if (!lst || !f)
		return (0);
	result = ft_lstnew(f(lst->content));
	if (!result)
		return (0);
	lst = lst->next;
	while (lst)
	{
		append = ft_lstnew(f(lst->content));
		if (!append)
		{
			ft_lstclear(&result, del);
			return (0);
		}
		ft_lstadd_back(&result, append);
		lst = lst->next;
	}
	return (result);
}
