/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 23:42:29 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/01 23:44:17 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*g_hex = "0123456789ABCDEF";

char	*ft_itoa_base(int value, int base)
{
	char	*ret;
	long	x;
	int		count;
	long	y;

	if (base < 2)
		return (NULL);
	x = (base == 10) ? value : 0;
	x = (base != 10) ? (unsigned int)value : x;
	y = x;
	count = (x < 0) ? 2 : 1;
	while (x > base - 1 || x < -9)
	{
		x /= base;
		count++;
	}
	ret = ft_strnew(count);
	ret[0] = ((value == 0) ? '0' : ret[0]);
	ret[0] = ((base == 10 && value < 0) ? '-' : ret[0]);
	while (y != 0)
	{
		ret[--count] = (g_hex[ABS(y % base)]);
		y /= base;
	}
	return (ret);
}
