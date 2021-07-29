/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saoh <saoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 13:25:02 by saoh              #+#    #+#             */
/*   Updated: 2020/11/04 15:13:32 by saoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memset(void *dest, int val, size_t size)
{
	char	*c_dest;

	c_dest = dest;
	while (size--)
		*((unsigned char *)c_dest++) = (unsigned char)val;
	return (dest);
}
