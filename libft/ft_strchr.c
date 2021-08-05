/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekang <taekang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 04:02:04 by taekang           #+#    #+#             */
/*   Updated: 2020/10/18 19:45:37 by taekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*result;
	int		i;

	i = 0;
	result = (char *)s;
	while (result[i])
	{
		if (result[i] == (char)c)
			return (result + i);
		i++;
	}
	if (result[i] == (char)c)
		return (result + i);
	return (0);
}
