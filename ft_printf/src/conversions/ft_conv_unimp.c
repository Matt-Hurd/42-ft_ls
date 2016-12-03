/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_unimp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 19:17:17 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/01 18:57:46 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_conv_unimp(char in, t_output *out, t_arg *flags, va_list *ap)
{
	(void)ap;
	(void)out;
	(void)in;
	(void)flags;
	out->str = ft_strnjoin(out->str, out->len, "unimplemented", 13);
	out->len += 13;
}
