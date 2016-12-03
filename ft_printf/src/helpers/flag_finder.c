/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 23:08:46 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/01 22:54:58 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	find_width_precision(char *in, int len, t_arg *ret)
{
	int x;

	x = 0;
	while (x < len)
	{
		if (in[x] != '0' && ft_isdigit(in[x]) && in[x - 1] != '.')
		{
			ret->got_width = 1;
			ret->width = ft_atoi(in + x);
			while (in[x] && ft_isdigit(in[x]))
				x++;
		}
		if (in[x] == '.' && in[x + 1] != '*')
		{
			ret->got_precis = 1;
			ret->precision = ft_atoi(in + x + 1);
			x++;
			while (in[x] && ft_isdigit(in[x]))
				x++;
		}
		x++;
	}
}

void	find_length(char *in, int len, t_arg *ret)
{
	int	x;

	x = -1;
	ret->length = none;
	while (++x < len)
	{
		if (in[x] == 'h' && ret->length < h)
			ret->length = (in[++x] == 'h') ? hh : h;
		else if (in[x] == 'l' && ret->length < ll)
			ret->length = (in[++x] == 'l') ? ll : l;
		else if (in[x] == 'L')
			ret->length = L;
		else if (in[x] == 'q')
			ret->length = q;
		else if (in[x] == 'j')
			ret->length = j;
		else if (in[x] == 'z')
			ret->length = z;
		else if (in[x] == 't')
			ret->length = t;
		else
			continue ;
	}
}

void	parse_asterisk(char *in, int x, t_arg *ret, va_list *ap)
{
	int found;

	if (in[x - 1] == '.')
	{
		found = va_arg(*ap, int);
		if (found >= 0)
		{
			ret->precision = found;
			ret->got_precis = 1;
		}
	}
	else
	{
		found = va_arg(*ap, int);
		if (found < 0)
			ret->left_justify = 1;
		ret->width = ABS(found);
		ret->got_width = 1;
	}
}

void	find_asterisk(char *in, t_arg *ret, va_list *ap, int len)
{
	int x;
	int found;

	x = -1;
	while (++x < len)
	{
		if (in[x] == '*' && !ft_isdigit(in[x + 1]))
			parse_asterisk(in, x, ret, ap);
		else if (in[x] == '*')
			found = va_arg(*ap, int);
	}
}

t_arg	*find_flags(char *in, int len, va_list *ap)
{
	t_arg	*ret;
	int		x;

	x = -1;
	ret = (t_arg *)ft_memalloc(sizeof(t_arg));
	while (++x < len)
	{
		if (in[x] == '#')
			ret->alternative = 1;
		if (in[x] == '0' && in[x - 1] != '.' && !ft_isdigit(in[x - 1]))
			ret->pad_zeroes = 1;
		if (in[x] == '-')
			ret->left_justify = 1;
		if (in[x] == ' ')
			ret->blank = 1;
		if (in[x] == '+')
			ret->force = 1;
		if (in[x] == '\'')
			ret->grouping = 1;
	}
	find_width_precision(in, len, ret);
	find_asterisk(in, ret, ap, len);
	find_length(in, len, ret);
	return (ret);
}
