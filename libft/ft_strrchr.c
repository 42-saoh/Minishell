/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekang <taekang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 01:58:05 by taekang           #+#    #+#             */
/*   Updated: 2020/10/19 00:53:41 by taekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*result;
	int		i;

	result = (char *)s;
	i = 0;
	while (result[i])
		i++;
	if (!c)
		return (result + i);
	i--;
	while (i >= 0)
	{
		if (result[i] == (char)c)
			return (result + i);
		i--;
	}
	return (0);
}
