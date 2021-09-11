/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekang <taekang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 12:04:00 by taekang           #+#    #+#             */
/*   Updated: 2021/08/31 15:59:26 by taekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;

	if (!s)
		return (0);
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (0);
	if (start >= ft_strlen(s))
		ft_strlcpy(dst, "", 2);
	else
		ft_strlcpy(dst, (s + start), len + 1);
	return (dst);
}
