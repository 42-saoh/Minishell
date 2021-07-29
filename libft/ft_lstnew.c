/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saoh <saoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 12:54:06 by saoh              #+#    #+#             */
/*   Updated: 2020/10/16 13:35:43 by saoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void *content)
{
	t_list	*newlst;

	if (!(newlst = malloc(sizeof(t_list))))
		return (NULL);
	newlst->next = (NULL);
	newlst->content = content;
	return (newlst);
}
