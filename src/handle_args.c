/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 09:09:28 by mhurd             #+#    #+#             */
/*   Updated: 2016/11/20 09:11:23 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	set_arg(t_args *args, char c)
{
	if (c == 'l')
		args->l = 1;
	else if (c == 'R')
		args->R = 1;
	else if (c == 'r')
		args->r = 1;
	else if (c == 'a')
		args->a = 1;
	else if (c == 't')
		args->t = 1;
	else if (c == 'f')
		args->f = 1;
}

void 	process_args(int ac, char **av, t_args *args)
{
	int count;
	int iter;

	count = 0;
	args->dir = 0;
	while (++count < ac)
	{
		if (av[count][0] == '-')
		{
			iter = 0;
			while (av[count][iter])
			{
				set_arg(args, av[count][iter]);
				iter++;
			}
		}
		else
		{
			if (args->dir)
				return ; //throw error
			args->dir = av[count];
		}
	}
}
