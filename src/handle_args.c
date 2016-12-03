/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 09:09:28 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/02 19:10:32 by mhurd            ###   ########.fr       */
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
	else if (c == '1')
		;
	else
	{
		ft_dprintf(2, "ls: illegal option -- %c\n", c);
		ft_dprintf(2, "usage: ls [-lsartR] [file ...]\n");
		exit(1);
	}
}

void 	process_args(int ac, char **av, t_args *args)
{
	int 	count;
	int 	iter;
	int 	x;
	t_path	tmp;
	int		end;

	count = 0;
	x = 0;
	args->count = 0;
	end = 0;
	while (++count < ac)
	{
		if (av[count][0] == '-' && !end && av[count][1])
		{
			iter = 1;
			while (av[count][iter])
			{
				if (av[count][iter] == '-' && !av[count][iter + 1] && iter == 1)
				{
					end = 1;
					break ;
				}
				set_arg(args, av[count][iter]);
				iter++;
			}
		}
		else
		{
			if (av[count][0] == 0)
			{
				ft_dprintf(2, "ls: fts_open: No such file or directory\n");
				exit(1);
			}
			if (ft_strequ(av[count], "-"))
				end = 1;
			tmp.filename = ft_strdup(av[count]);
			if (tmp.filename)
				ft_lst_add_back(&args->dirs_pre, ft_lstnew(&tmp, sizeof(t_path)));
			args->count++;
		}
	}
}
