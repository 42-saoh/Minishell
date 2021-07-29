/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saoh <saoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 19:28:10 by saoh              #+#    #+#             */
/*   Updated: 2020/11/04 15:40:08 by saoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t				ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t			i;
	size_t			dest_len;
	size_t			src_len;

	i = 0;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen((char *)src);
	if (dest_len < n - 1 && n > 0)
	{
		while (i + dest_len < n - 1 && i < src_len)
		{
			dest[i + dest_len] = src[i];
			i++;
		}
		dest[i + dest_len] = 0;
	}
	if (dest_len < n)
		return (dest_len + src_len);
	return (src_len + n);
}
