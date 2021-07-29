/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saoh <saoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 14:38:50 by saoh              #+#    #+#             */
/*   Updated: 2020/11/04 14:45:40 by saoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_calloc(size_t elt_count, size_t elt_size)
{
	size_t	i;
	void	*temp;
	void	*c_temp;

	i = elt_count * elt_size;
	if (!(temp = (void *)malloc(i)))
		return (NULL);
	c_temp = temp;
	while (i--)
	{
		*((char *)c_temp++) = 0;
	}
	return (temp);
}
