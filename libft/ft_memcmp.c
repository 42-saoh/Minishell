/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saoh <saoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 10:20:56 by saoh              #+#    #+#             */
/*   Updated: 2020/10/21 11:51:15 by saoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *ptr1, const void *ptr2, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		if (*((unsigned char *)ptr1 + i) != (*((unsigned char *)ptr2 + i)))
			return ((*((unsigned char *)ptr1 + i)
						- (*((unsigned char *)ptr2 + i))));
		else
			i++;
	}
	return (0);
}
