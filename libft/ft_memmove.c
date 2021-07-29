/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saoh <saoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 16:31:23 by saoh              #+#    #+#             */
/*   Updated: 2020/11/04 15:10:56 by saoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*c_dest;
	unsigned char		*c_src;

	if (dest == src || n == 0)
		return (dest);
	c_dest = (unsigned char *)dest;
	c_src = (unsigned char *)src;
	if (dest < src)
	{
		while (n--)
			*(c_dest++) = *(c_src++);
	}
	else
	{
		while (n--)
			*(c_dest + n) = *(c_src + n);
	}
	return (dest);
}
