/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saoh <saoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 11:07:11 by saoh              #+#    #+#             */
/*   Updated: 2020/11/04 14:20:49 by saoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	long	minus;
	long	val;

	minus = 1;
	val = 0;
	while (((*str >= 9 && *str <= 13) || *str == ' ') && *str != 0)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			minus = -1;
		str++;
	}
	while ((*str >= '0' && *str <= '9') && *str != 0)
	{
		val = (val * 10) + (*str - '0');
		if (val * minus > 2147483647)
			return (-1);
		else if (val * minus < -2147483648)
			return (0);
		str++;
	}
	return (val * minus);
}
