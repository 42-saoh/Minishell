/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saoh <saoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:31:26 by saoh              #+#    #+#             */
/*   Updated: 2020/10/08 17:44:40 by saoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strrchr(const char *s, int c)
{
	size_t		i;
	char		*fp;

	i = 0;
	fp = (char *)s;
	while (s[i])
		i++;
	if (s[i] == c)
		return ((char *)s + i);
	i--;
	while (s[i] >= 0 && s[i])
	{
		if (s[i] == c)
			return ((char *)s + i);
		else if (s + i == fp)
			break ;
		i--;
	}
	if (s[i] == c)
		return ((char *)s + i);
	return (NULL);
}
