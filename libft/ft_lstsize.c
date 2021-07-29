/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saoh <saoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 14:20:12 by saoh              #+#    #+#             */
/*   Updated: 2020/10/16 14:27:41 by saoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_lstsize(t_list *lst)
{
	t_list	*curr;
	int		i;

	if (lst == NULL)
		return (0);
	i = 1;
	curr = lst->next;
	while (curr != 0)
	{
		curr = curr->next;
		i++;
	}
	return (i);
}
