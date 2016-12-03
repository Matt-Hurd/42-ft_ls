/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 23:26:10 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/01 23:27:14 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_conv_wc(char **str, va_list *ap)
{
	wchar_t in;
	int		len;

	in = va_arg(*ap, wchar_t);
	len = wchar_len(in);
	*str = ft_strnew(len);
	wchar_to_str(in, *str);
	return (in == 0);
}

void	handle_null(char *str, t_output *out, char null)
{
	size_t	len;
	size_t	pos;

	len = ft_strlen(str);
	pos = 0;
	while (pos < len)
	{
		if (str[pos] == null)
			str[pos] = 0;
		pos++;
	}
	out->str = ft_strnjoin(out->str, out->len, str, len);
	out->len += len;
}

void	ft_conv_c(char in, t_output *out, t_arg *flags, va_list *ap)
{
	int		c;
	char	*str;
	char	null;

	null = 0;
	if (in == 'C' || flags->length == l)
	{
		null = ft_conv_wc(&str, ap);
		str[0] = (null) ? null : str[0];
	}
	else
	{
		c = va_arg(*ap, int);
		str = ft_strnew(1);
		null = (c == 0) ? 1 : 0;
		str[0] = c + null;
	}
	handle_padding(&str, flags, 's');
	if (null)
		handle_null(str, out, null);
	else
	{
		out->str = ft_strnjoin(out->str, out->len, str, ft_strlen(str));
		out->len += ft_strlen(str);
	}
}
