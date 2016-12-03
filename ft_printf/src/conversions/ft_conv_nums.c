/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_nums.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 23:32:04 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/02 00:00:37 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_upper(char *str, char in)
{
	if (in != 'X')
		return ;
	while (*str)
	{
		if (ft_isalpha(*str))
			*str = ft_toupper(*str);
		str++;
	}
}

void	handle_alternative(char **str, t_arg *flags, char in)
{
	if ((!flags->alternative && in != 'p'))
		return ;
	flags->pad_zeroes = 0;
	if ((in == 'x' || in == 'X' || in == 'p') && ft_strcmp("0", *str)
		&& !(flags->precision == 0 && flags->got_precis))
		*str = ft_strjoinf("0x", *str);
	else if ((in == 'o' || in == 'O') && (*str)[0] != '0')
		*str = ft_strjoinf("0", *str);
}

void	pop_num(char *in, t_arg *flags, va_list *ap, uintmax_t *num)
{
	*in = (*in == 'i') ? 'd' : *in;
	if (*in == 'p')
	{
		flags->alternative = 1;
		flags->length = p;
	}
	flags->length = (*in == 'U' || *in == 'D' || *in == 'O')
		? l : flags->length;
	*in = (*in == 'D') ? 'd' : *in;
	if (flags->length == l || flags->length == p)
		*num = va_arg(*ap, long);
	else if (flags->length == hh)
		*num = va_arg(*ap, int);
	else if (flags->length == h)
		*num = va_arg(*ap, int);
	else if (flags->length == ll || flags->length == q)
		*num = va_arg(*ap, long long);
	else if (flags->length == z)
		*num = va_arg(*ap, size_t);
	else if (flags->length == j)
		*num = va_arg(*ap, intmax_t);
	else
		*num = va_arg(*ap, int);
}

void	handle_nums(char **str, t_arg *flags, char *in)
{
	if (flags->got_precis && flags->precision == 0 && !ft_strcmp(*str, "0"))
		*str[0] = 0;
	if (((flags->force || flags->blank) && *str[0] != '-') && *in == 'd')
	{
		*str = ft_strjoinf(flags->blank ? " " : "+", *str);
		*str[0] = flags->force ? '+' : *str[0];
	}
	handle_precision(str, flags, (*in == 'd' || *in == 'p') ? 'd' : 'u');
	if (*in == 'x' && flags->pad_zeroes && flags->alternative)
	{
		flags->width = MAX(flags->width - 2, 0);
		handle_padding(str, flags, (*in == 'd') ? 'd' : 'u');
	}
	handle_alternative(str, flags, *in);
	if (((flags->force || flags->blank) && *str[0] != '-') && (*in == 'p'))
	{
		*str = ft_strjoinf(flags->blank ? " " : "+", *str);
		*str[0] = flags->force ? '+' : *str[0];
	}
	if (!(*in == 'x' && flags->pad_zeroes && flags->alternative))
		handle_padding(str, flags, (*in == 'd') ? 'd' : 'u');
	handle_upper(*str, *in);
}

void	ft_conv_nums(char in, t_output *out, t_arg *flags, va_list *ap)
{
	uintmax_t	num;
	char		*str;
	char		nill;

	pop_num(&in, flags, ap, &num);
	str = ft_num_to_base(num, find_base(in), find_sign(in), flags->length);
	nill = (in == 'p' && ft_strcmp(str, "0") == 0) ? 1 : 0;
	if (nill)
	{
		handle_precision(&str, flags, 'd');
		if (flags->pad_zeroes)
		{
			flags->width = MAX(flags->width - 2, 0);
			handle_padding(&str, flags, 's');
		}
		if (flags->precision == 0 && flags->got_precis)
			str = ft_strdup("");
		str = ft_strjoinf("0x", str);
		if (!flags->pad_zeroes)
			handle_padding(&str, flags, 's');
	}
	else
		handle_nums(&str, flags, &in);
	out->str = ft_strnjoin(out->str, out->len, str, ft_strlen(str));
	out->len += ft_strlen(str);
}
