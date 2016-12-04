/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 19:40:22 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/02 19:58:13 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		gen_info(t_path *dest, char *dir, char *filename)
{
	char	*tmp;

	tmp = ft_strjoin(dir, filename);
	errno = 0;
	if (lstat(tmp, &dest->stats) == -1)
	{
		ft_dprintf(2, "ls: %s: %s\n", tmp, strerror(errno));
		dest->filename = 0;
		free(tmp);
		return ;
	}
	free(tmp);
	dest->filename = ft_strdup(filename);
}

int			year_length(time_t t)
{
	long	diff;

	diff = time(0) - t;
	if (diff > 15552000 || diff < -15552000)
		return (4);
	else
		return (5);
}

void		clear_args(t_args *args)
{
	args->l = 0;
	args->lr = 0;
	args->r = 0;
	args->a = 0;
	args->f = 0;
	args->t = 0;
}

blkcnt_t	add_blocks(t_list *list)
{
	blkcnt_t ret;

	ret = 0;
	while (list)
	{
		ret += ((t_path *)list->content)->stats.st_blocks;
		list = list->next;
	}
	return (ret);
}
