/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saoh <saoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 14:33:47 by saoh              #+#    #+#             */
/*   Updated: 2020/10/16 14:43:12 by saoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstlast(t_list *lst)
{
	t_list *curr;

	if (lst == NULL)
		return (NULL);
	else if (lst->next == NULL)
		return (lst);
	curr = lst->next;
	while (curr->next != NULL)
	{
		curr = curr->next;
	}
	return (curr);
}
