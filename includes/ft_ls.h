/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 03:52:57 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/02 18:50:57 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft.h"
# include "ft_printf.h"
# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <time.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/syslimits.h>

typedef struct	s_args
{
	char			*dir;
	unsigned int	l : 1;
	unsigned int	R : 1;
	unsigned int	r : 1;
	unsigned int	a : 1;
	unsigned int	t : 1;
	unsigned int	f : 1;
	t_list			*dirs;
	t_list			*dirs_pre;
	int				count;
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
int		dir_cmp(t_path *path, t_path *next, char order);
void	gen_info(t_path *dest, char *dir, char *filename);

#endif
