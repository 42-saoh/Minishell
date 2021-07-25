/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekang <taekang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 16:51:51 by taekang           #+#    #+#             */
/*   Updated: 2020/10/19 20:18:02 by taekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		is_possible(char c, char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

int		get_start(char const *s1, char *set)
{
	int		i;
	char	*char_s1;

	char_s1 = (char *)s1;
	i = 0;
	while (s1[i] && is_possible(char_s1[i], set))
		i++;
	return (i);
}

int		get_end(char const *s1, char *set, int r, int l)
{
	char *char_s1;

	char_s1 = (char *)s1;
	while (s1[r] && r >= l && is_possible(char_s1[r], set))
		r--;
	return (r);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	int		start;
	int		end;
	int		len;

	if (!s1 || !set)
		return (0);
	len = ft_strlen(s1);
	end = len;
	start = get_start(s1, (char *)set);
	end = get_end(s1, (char *)set, len - 1, start);
	if (!(result = (char *)malloc(sizeof(char) * (end - start + 2))))
		return (0);
	ft_strlcpy(result, s1 + start, (end - start + 2));
	return (result);
}
