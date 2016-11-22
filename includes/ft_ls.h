/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 03:52:57 by mhurd             #+#    #+#             */
/*   Updated: 2016/11/20 09:09:52 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>

typedef struct	s_args
{
	char			*dir;
	unsigned int	l : 1;
	unsigned int	R : 1;
	unsigned int	r : 1;
	unsigned int	a : 1;
	unsigned int	t : 1;
	unsigned int	f : 1;
}				t_args;

typedef struct	s_path
{
	struct stat stats;
	char		*filename;
}				t_path;

void 	ft_lstsort(t_list *start, char order,
			int (*f)(t_path *, t_path *, char));
int		name_cmp(t_path *path, t_path *next, char order);
int		time_cmp(t_path *path, t_path *next, char order);
void 	process_args(int ac, char **av, t_args *args);

#endif
