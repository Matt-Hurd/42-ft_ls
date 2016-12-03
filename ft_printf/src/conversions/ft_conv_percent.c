/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_percent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 23:28:06 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/01 23:28:29 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_conv_percent(char in, t_output *out, t_arg *flags, va_list *ap)
{
	char	*str;

	(void)ap;
	str = ft_strnew(1);
	str[0] = in;
	handle_padding(&str, flags, '%');
	out->str = ft_strnjoin(out->str, out->len, str, ft_strlen(str));
	out->len += ft_strlen(str);
}
