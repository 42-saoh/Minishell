/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saoh <saoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 17:47:29 by saoh              #+#    #+#             */
/*   Updated: 2020/10/08 14:18:52 by saoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_val_ct(long val, int m)
{
	int			ct;

	ct = 0;
	while (val > 0)
	{
		val = val / 10;
		ct++;
	}
	if (m < 0)
		ct++;
	return (ct);
}

static char		*ft_toa(long val, int m)
{
	int			ct;
	char		*str;

	if (val < 0)
	{
		m = -m;
		val = -val;
	}
	ct = ft_val_ct(val, m);
	if (!(str = (char *)malloc(sizeof(char) * (ct + 1))))
		return (NULL);
	str[ct] = 0;
	while (val > 0)
	{
		str[--ct] = (val % 10) + '0';
		val = val / 10;
	}
	if (m < 0)
		str[0] = '-';
	return (str);
}

char			*ft_itoa(int n)
{
	long		val;
	int			m;
	char		*str;

	m = 1;
	if (n > 0 || n < 0)
	{
		val = (long)n;
		if ((str = ft_toa(val, m)) == NULL)
			return (NULL);
	}
	else
	{
		if (!(str = (char *)malloc(sizeof(char) * 2)))
			return (NULL);
		str[0] = '0';
		str[1] = 0;
	}
	return (str);
}
