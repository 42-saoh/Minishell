/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saoh <saoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:27:46 by saoh              #+#    #+#             */
/*   Updated: 2020/11/04 15:01:09 by saoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	while (n--)
	{
		if (*((unsigned char *)src) == (unsigned char)c)
		{
			*((unsigned char *)dest) = *((unsigned char *)src);
			return (dest + 1);
		}
		*((unsigned char *)dest++) = *((unsigned char *)src++);
	}
	return (NULL);
}
