/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekang <taekang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 17:15:56 by taekang           #+#    #+#             */
/*   Updated: 2020/10/19 18:47:48 by taekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*str_dst;
	const char	*str_src;

	if (!dst && !src)
		return (0);
	str_dst = (char *)dst;
	str_src = (const char *)src;
	if (dst <= src)
	{
		while (len--)
			*str_dst++ = *str_src++;
	}
	else
	{
		while (len > 0)
		{
			str_dst[(len - 1)] = str_src[(len - 1)];
			len--;
		}
	}
	return (dst);
}
