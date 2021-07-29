/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saoh <saoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 17:17:20 by saoh              #+#    #+#             */
/*   Updated: 2020/10/18 14:26:48 by saoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *str1, const char *str2, size_t len)
{
	size_t	i;
	size_t	ct;
	size_t	str1_len;
	size_t	str2_len;

	i = 0;
	str1_len = ft_strlen(str1);
	str2_len = ft_strlen(str2);
	if (str2_len == 0)
		return ((char *)str1);
	while (i < len && i < str1_len)
	{
		ct = 0;
		while (ct < str2_len && i + ct < len && i + ct < str1_len)
		{
			if (str1[i + ct] != str2[ct])
				break ;
			ct++;
			if (ct == str2_len)
				return ((char *)str1 + i);
		}
		i++;
	}
	return (NULL);
}
