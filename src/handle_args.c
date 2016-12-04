/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 16:50:09 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/03 17:05:23 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	set_arg(t_args *args, char c)
{
	if (c == 'l')
		args->l = 1;
	else if (c == 'R')
		args->lr = 1;
	else if (c == 'r')
		args->r = 1;
	else if (c == 'a')
		args->a = 1;
	else if (c == 't')
		args->t = 1;
	else if (c == 'f')
		args->f = 1;
	else if (c == '1')
		args->l = 0;
	else if (c == 'T')
		args->lt = 1;
	else
	{
		ft_dprintf(2, "ls: illegal option -- %c\n", c);
		ft_dprintf(2, "usage: ls [-lsartR] [file ...]\n");
		exit(1);
	}
}

void	handle_dash(char **av, int count, int *end, t_args *args)
{
	int iter;

	iter = 1;
	while (av[count][iter])
	{
		if (av[count][iter] == '-' && !av[count][iter + 1] && iter == 1)
		{
			*end = 1;
			break ;
		}
		set_arg(args, av[count][iter++]);
	}
}

void	process_args(int ac, char **av, t_args *args)
{
	int		count;
	t_path	tmp;
	int		end;

	count = 0;
	args->count = 0;
	end = 0;
	while (++count < ac)
	{
		if (av[count][0] == '-' && !end && av[count][1])
			handle_dash(av, count, &end, args);
		else
		{
			if (av[count][0] == 0)
			{
				ft_dprintf(2, "ls: fts_open: No such file or directory\n");
				exit(1);
			}
			end = (ft_strequ(av[count], "-")) ? 1 : end;
			tmp.filename = ft_strdup(av[count]);
			ft_lst_add_back(&args->dirs_pre, ft_lstnew(&tmp, sizeof(t_path)));
			args->count++;
		}
	}
}
