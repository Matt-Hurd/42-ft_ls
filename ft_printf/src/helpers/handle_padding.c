/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_padding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 22:43:43 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/01 22:49:17 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	right_justify(char **str, t_arg *flags, char type, char *n)
{
	char alt;

	alt = 0;
	if (flags->pad_zeroes)
	{
		alt = (!ft_isalnum((*str)[0]) && type == 'd') ? (*str)[0] : 0;
		ft_memset(n, '0', flags->width - ft_strlen(*str) + !!alt);
		if (alt)
			n[0] = alt;
		if (alt)
			(*str)[0] = '0';
	}
	else
	{
		ft_memset(n, ' ', flags->width - ft_strlen(*str));
		if (flags->force || (*str)[0] == '-')
			n[flags->width - ft_strlen(*str)] = ((*str)[0] == '-') ? '-' : '+';
	}
	ft_strcpy(n + flags->width - ft_strlen(*str) + !!alt, *str + !!alt);
}

void	handle_padding(char **str, t_arg *flags, char type)
{
	char	*n;

	if (!flags->got_width)
		return ;
	if (ft_strlen(*str) >= flags->width)
		return ;
	n = ft_strnew(flags->width);
	if (flags->left_justify)
	{
		ft_strcpy(n, *str);
		ft_memset(n + ft_strlen(*str), ' ', flags->width - ft_strlen(*str));
	}
	else
		right_justify(str, flags, type, n);
	*str = n;
}
