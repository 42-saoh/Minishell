/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saoh <saoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 14:25:04 by saoh              #+#    #+#             */
/*   Updated: 2020/11/04 17:13:38 by saoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*c_dest;

	if (src == 0 && dest == 0)
	{
		dest = 0;
		return (dest);
	}
	c_dest = dest;
	while (n--)
	{
		*((unsigned char *)c_dest++) = *((unsigned char *)src++);
	}
	return (dest);
}
