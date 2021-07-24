/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekang <taekang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 14:21:37 by taekang           #+#    #+#             */
/*   Updated: 2020/10/19 20:17:17 by taekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	int		s1_len;
	int		s2_len;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!(dst = (char *)malloc(s1_len + s2_len + 1)))
		return (0);
	ft_strlcpy(dst, s1, (s1_len + 1));
	ft_strlcpy(dst + s1_len, s2, (s2_len + 1));
	return (dst);
}
