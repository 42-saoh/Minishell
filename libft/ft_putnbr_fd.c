/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saoh <saoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 18:53:25 by saoh              #+#    #+#             */
/*   Updated: 2020/11/04 15:16:12 by saoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_nbr(long val, int fd)
{
	char		a[10];
	int			i;

	i = 0;
	while (val > 0)
	{
		a[i++] = val % 10 + '0';
		val = val / 10;
	}
	while (i-- > 0)
		write(fd, &a[i], 1);
}

void			ft_putnbr_fd(int n, int fd)
{
	long		val;

	if (n > 0)
	{
		val = (long)n;
		ft_nbr(val, fd);
	}
	else if (n < 0)
	{
		val = (long)n;
		val = -val;
		write(fd, "-", 1);
		ft_nbr(val, fd);
	}
	else
		write(fd, "0", 1);
}
