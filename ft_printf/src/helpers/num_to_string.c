/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_to_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 22:58:26 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/01 23:00:33 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char g_hex[] = "0123456789abcdef";

int		handle_unsign(uintmax_t *value, char type)
{
	if (type == l && *value > LONG_MAX)
		*value = *value - (UINTMAX_MAX - ULONG_MAX);
	else if (type == ll && *value > LLONG_MAX)
		*value = *value - (UINTMAX_MAX - ULLONG_MAX);
	else if (type == h && *value > SHRT_MAX)
	{
		*value = *value - (UINTMAX_MAX) - 1;
		*value %= (USHRT_MAX) + 1;
	}
	else if (type == hh && *value > SCHAR_MAX)
	{
		*value = *value - (UINTMAX_MAX) - 1;
		*value %= (UCHAR_MAX) + 1;
	}
	else if (*value > INT_MAX && type != hh && type != h
		&& type != ll && type != l && type != j && type != z)
		*value = *value - (UINTMAX_MAX - UINT_MAX);
	if (type == p && *value > 0x100000000)
		*value -= 0x100000000;
	return (1);
}

int		handle_schar(uintmax_t *value)
{
	*value %= UCHAR_MAX;
	if (*value > CHAR_MAX)
	{
		*value = UINTMAX_MAX - (*value - UCHAR_MAX) + 2;
		return (2);
	}
	return ((char)*value < 0 ? 2 : 1);
}

int		handle_sign(uintmax_t *value, t_u32 base, char unsign, char type)
{
	if (unsign || base != 10)
		return (handle_unsign(value, type));
	else if (type == j && *value == (unsigned long)LONG_MIN)
		;
	else if (type == hh && *value > SCHAR_MAX)
		return (handle_schar(value));
	else if (type == h && *value > SHRT_MAX)
	{
		*value %= USHRT_MAX;
		return ((short)*value < 0 ? 2 : 1);
	}
	else if (type == l && *value > LONG_MAX)
		*value = ULONG_MAX - (unsigned long)(*value) + 1;
	else if (type == ll && *value > LLONG_MAX)
		*value = ULLONG_MAX - (unsigned long long)(*value) + 1;
	else if ((type == j || type == z) && *value > (uintmax_t)INTMAX_MIN)
		*value = UINTMAX_MAX - *value + 1;
	else if (*value > INT_MAX && type != hh && type != h && type != ll
		&& type != l && type != j && type != z)
		*value = UINT_MAX - (unsigned int)(*value) + 1;
	else
		return (1);
	return (2);
}

char	*ft_num_to_base(uintmax_t value, t_u32 base, char unsign, char type)
{
	char		*ret;
	uintmax_t	x;
	int			count;
	int			neg;

	if (base < 2)
		return (NULL);
	count = handle_sign(&value, base, unsign, type);
	neg = ((count == 2) ? 1 : 0);
	x = value;
	while (x > base - 1)
	{
		x /= base;
		count++;
	}
	ret = ft_strnew(count);
	x = value;
	ret[0] = ((value == 0) ? '0' : ret[0]);
	ret[0] = (neg ? '-' : ret[0]);
	while (x != 0)
	{
		ret[--count] = (g_hex[x % base]);
		x /= base;
	}
	return (ret);
}
