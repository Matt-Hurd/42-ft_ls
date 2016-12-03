/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 23:47:41 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/01 23:47:48 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		find_base(char in)
{
	if (in == 'o' || in == 'O')
		return (8);
	else if (in == 'x' || in == 'X' || in == 'p')
		return (16);
	else if (in == 'b')
		return (2);
	else
		return (10);
}

int		find_sign(char in)
{
	if (in == 'd' || in == 'i')
		return (0);
	return (1);
}
