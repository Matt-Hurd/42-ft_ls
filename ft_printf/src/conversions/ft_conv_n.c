/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_n.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 23:28:56 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/01 23:28:59 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_conv_n(char in, t_output *out, t_arg *flags, va_list *ap)
{
	int	*storage;

	(void)in;
	(void)flags;
	storage = va_arg(*ap, int *);
	*storage = out->len;
}
