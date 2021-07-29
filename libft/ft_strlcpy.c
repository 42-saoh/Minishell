/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saoh <saoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 19:46:51 by saoh              #+#    #+#             */
/*   Updated: 2020/11/04 15:39:10 by saoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	src_len;

	if (src == 0)
		return (0);
	src_len = ft_strlen(src);
	if (n-- == 0)
		return (src_len);
	while (n-- && *src)
		*dest++ = *src++;
	*dest = 0;
	return (src_len);
}
