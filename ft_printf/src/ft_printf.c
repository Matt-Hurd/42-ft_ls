/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 17:28:58 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/02 18:19:49 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*g_convs = "diouxXDOUeEfFgGaACcSspn%Z";
char	*g_valid = "diouxXDOUeEfFgGaACcSspn%Z.+-#0123456789\' *hlLqjzt";

t_conv g_convtab[] =
{
	{"d", &ft_conv_nums},
	{"i", &ft_conv_nums},
	{"o", &ft_conv_nums},
	{"u", &ft_conv_nums},
	{"x", &ft_conv_nums},
	{"X", &ft_conv_nums},
	{"D", &ft_conv_nums},
	{"O", &ft_conv_nums},
	{"U", &ft_conv_nums},
	{"e", &ft_conv_unimp},
	{"E", &ft_conv_unimp},
	{"f", &ft_conv_unimp},
	{"F", &ft_conv_unimp},
	{"g", &ft_conv_unimp},
	{"G", &ft_conv_unimp},
	{"a", &ft_conv_unimp},
	{"A", &ft_conv_unimp},
	{"C", &ft_conv_c},
	{"c", &ft_conv_c},
	{"S", &ft_conv_s},
	{"s", &ft_conv_s},
	{"p", &ft_conv_nums},
	{"n", &ft_conv_n},
	{"%", &ft_conv_percent},
	{"Z", &ft_conv_percent}
};

void	do_conversion(char **in, t_output *out, va_list *ap, unsigned int len)
{
	int		pos_in_tab;
	t_arg	*flags;

	flags = find_flags(*in, len, ap);
	pos_in_tab = ft_strchr(g_convs, (*in)[len]) - g_convs;
	if (pos_in_tab < 0)
		ft_conv_percent((*in)[len], out, flags, ap);
	else
		g_convtab[pos_in_tab].ft((*in)[len], out, flags, ap);
	*in += len + 1;
}

void	get_next_string(char **in, t_output *out, va_list *ap)
{
	char			*tmp;
	long			dist;

	tmp = *in;
	dist = ft_strchr(tmp, '%') - tmp;
	if (dist < 0)
		dist = ft_strchr(*in, '\0') - tmp;
	if (dist != 0)
	{
		out->str = ft_strnjoin(out->str, out->len, tmp, dist);
		out->len += dist;
		*in += dist;
		return ;
	}
	tmp++;
	while (*tmp && !ft_strchr(g_convs, *tmp) && ft_strchr(g_valid, *tmp))
		tmp++;
	if (*tmp)
		do_conversion(in, out, ap, tmp - *in);
	else
		*in = tmp;
}

int		ft_printf(char *in, ...)
{
	va_list		ap;
	va_list		ap2;
	t_output	out;

	va_start(ap, in);
	va_copy(ap2, ap);
	out.str = ft_strnew(0);
	out.len = 0;
	while (*in)
		get_next_string(&in, &out, &ap);
	write(1, out.str, out.len);
	return (out.len);
}

int		ft_dprintf(int fd, char *in, ...)
{
	va_list		ap;
	va_list		ap2;
	t_output	out;

	va_start(ap, in);
	va_copy(ap2, ap);
	out.str = ft_strnew(0);
	out.len = 0;
	while (*in)
		get_next_string(&in, &out, &ap);
	write(fd, out.str, out.len);
	return (out.len);
}

int		ft_asprintf(char **str, char *in, ...)
{
	va_list		ap;
	va_list		ap2;
	t_output	out;

	va_start(ap, in);
	va_copy(ap2, ap);
	out.str = ft_strnew(0);
	out.len = 0;
	while (*in)
		get_next_string(&in, &out, &ap);
	*str = out.str;
	return (out.len);
}
