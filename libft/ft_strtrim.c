/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saoh <saoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 21:18:36 by saoh              #+#    #+#             */
/*   Updated: 2020/11/04 17:06:35 by saoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_find(char *c_s1, char const *set, int flag)
{
	char const	*c_set;

	c_set = set;
	if (flag == 1)
	{
		while (*c_s1)
			c_s1++;
		c_s1--;
	}
	while (*c_set)
	{
		if (*c_s1 == *c_set)
		{
			c_set = set;
			if (flag == 1)
				c_s1--;
			else
				c_s1++;
			continue ;
		}
		c_set++;
	}
	return (c_s1);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char		*trim;
	char		*c_s1;
	char		*last_s;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	c_s1 = (char *)s1;
	c_s1 = ft_find(c_s1, set, 0);
	if (*c_s1 == 0)
		return (ft_strdup(""));
	last_s = ft_find(c_s1, set, 1);
	trim = ft_substr(c_s1, 0, last_s - c_s1 + 1);
	return (trim);
}
