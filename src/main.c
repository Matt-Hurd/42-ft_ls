/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 15:35:03 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/02 19:17:03 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	gen_info(t_path *dest, char *dir, char *filename)
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

#include <math.h>

int num_len(unsigned long long x)
{
	return floor(log10(x)) + 1;
}

int		year_length(time_t t)
{
	long	diff;

	diff = time(0) - t;
	if (diff > 15552000 || diff < -15552000)
		return (4);
	else
		return (5);
}

void	set_widths(int widths[5], t_list *files)
{
	struct stat		stats;
	struct passwd	*pwd;
	struct group	*grp;

	widths[0] = 0;
	widths[1] = 0;
	widths[2] = 0;
	widths[3] = 0;
	widths[4] = 0;
	while (files)
	{
		stats = ((t_path *)files->content)->stats;
		pwd = getpwuid(stats.st_uid);
		grp = getgrgid(stats.st_gid);
		widths[0] = MAX(num_len(stats.st_nlink), widths[0]);
		widths[1] = MAX((int)ft_strlen(pwd->pw_name) + 1, widths[1]);
		widths[2] = MAX((int)ft_strlen(grp->gr_name), widths[2]);
		widths[3] = MAX(num_len(stats.st_size), widths[3]);
		widths[4] = MAX(year_length(stats.st_mtime), widths[4]);
		files = files->next;
	}
	widths[0]++;
}

void	clear_args(t_args *args)
{
	args->l = 0;
	args->R = 0;
	args->r = 0;
	args->a = 0;
	args->f = 0;
	args->t = 0;
}

char	*time_string(time_t t)
{
	char *str;
	char *end;
	char **buff;
	char **buff2;

	buff = ft_strsplit(ft_strtrim(ctime(&t)), ' ');
	buff2 = ft_strsplit(buff[3], ':');
	if (year_length(t) == 4)
		ft_asprintf(&end, "%s", buff[4]);
	else
		ft_asprintf(&end, "%s:%s", buff2[0], buff2[1]);
	ft_asprintf(&str, "%s %2s %*s", buff[1], buff[2], 5, end);
	free(buff);
	free(buff2);
	return(str);
}

blkcnt_t	add_blocks(t_list *list)
{
	blkcnt_t ret;

	ret = 0;
	while(list)
	{
		ret += ((t_path *)list	->content)->stats.st_blocks;
		list = list->next;
	}
	return (ret);
}

void	print_file(t_args args, t_path *file, int widths[5])
{
	struct stat stats;
	char sympath[PATH_MAX];
	struct passwd	*pwd;
	struct group	*grp;

	if (args.l)
	{
		stats = file->stats;
		pwd = getpwuid(stats.st_uid);
		grp = getgrgid(stats.st_gid);
		if (S_ISLNK(stats.st_mode))
			ft_printf("l");
		else
			ft_printf(S_ISDIR(stats.st_mode) ? "d" : "-");
		ft_printf((stats.st_mode & S_IRUSR) ? "r" : "-");
		ft_printf((stats.st_mode & S_IWUSR) ? "w" : "-");
		ft_printf((stats.st_mode & S_IXUSR) ? "x" : "-");
		ft_printf((stats.st_mode & S_IRGRP) ? "r" : "-");
		ft_printf((stats.st_mode & S_IWGRP) ? "w" : "-");
		ft_printf((stats.st_mode & S_IXGRP) ? "x" : "-");
		ft_printf((stats.st_mode & S_IROTH) ? "r" : "-");
		ft_printf((stats.st_mode & S_IWOTH) ? "w" : "-");
		ft_printf((stats.st_mode & S_IXOTH) ? "x" : "-");
		ft_printf(" %*d %-*s %-*s ", widths[0], stats.st_nlink, widths[1], pwd->pw_name, widths[2], grp->gr_name);
		ft_printf(" %*lld %s ", widths[3], stats.st_size, time_string(stats.st_mtime));
	}
	if (S_ISLNK(stats.st_mode) && args.l)
	{
		char *tmp;
		if (ft_strequ(args.dir, file->filename))
			tmp = file->filename;
		else
			tmp = ft_strjoin(args.dir, file->filename);
		readlink(tmp, sympath, PATH_MAX - 1);
		ft_printf("%s -> %s\n", file->filename, sympath);
	}
	else
		ft_printf("%s\n", file->filename);
}

void	do_ls(t_args args)
{
	struct	dirent *dir;
	DIR		*d;
	t_list	*files;
	t_list	*iter;
	int		count;
	t_path	path;
	int		widths[5];
	blkcnt_t blkcount;
	char	*current_dir;

	files = 0;
	count = 0;
	args.dir = ft_strjoin(args.dir ? args.dir : ".", "/");
	current_dir = ft_strdup(args.dir);
	errno = 0;
	d = opendir(args.dir);
	if (errno)
	{
		if (errno == 13)
		{
			ft_dprintf(2, "ls: %s: %s\n", args.dir, strerror(errno));
			return ;
		}
		args.dir[ft_strlen(args.dir) - 1] = 0;
		errno = 0;
		gen_info(&path, "", args.dir);
		if (errno)
		{
			ft_dprintf(2, "ls: %s: %s\n", args.dir, strerror(errno));
			return ;
		}
		ft_lst_add_back(&files, ft_lstnew(&path, sizeof(t_path)));
	}
	else
	{
		while ((dir = readdir(d)))
		{
			count += 1;
			if (!args.a && dir->d_name[0] == '.')
				continue;
			gen_info(&path, args.dir, dir->d_name);
			ft_lst_add_back(&files, ft_lstnew(&path, sizeof(t_path)));
		}
		ft_lstsort(files, args.r, args.t ? time_cmp : name_cmp);
		closedir(d);
		blkcount = add_blocks(files);
		if (args.l && files)
			ft_printf("total %lld\n", blkcount);
	}
	set_widths(widths, files);
	iter = files;
	while (iter)
	{
		print_file(args, iter->content, widths);
		iter = iter->next;
	}
	if (args.R)
	{
		iter = files;
		while (iter)
		{
			if (S_ISDIR(((t_path *)iter->content)->stats.st_mode) &&
				!(ft_strequ(((t_path *)iter->content)->filename, ".")
				|| ft_strequ(((t_path *)iter->content)->filename, "..")))
			{
				ft_printf("\n");
				ft_printf("%s%s:\n", current_dir, ((t_path *)iter->content)->filename);
				args.dir = ft_strjoin(current_dir, ((t_path *)iter->content)->filename);
				do_ls(args);
			}
			iter = iter->next;
		}
	}
}

int		main(int ac, char **av)
{
	t_args		args;
	int			x;
	t_path		*path;
	struct stat	stats;
	int			sym_is_dir;

	clear_args(&args);
	args.dirs = 0;
	process_args(ac, av, &args);
	x = -1;
	if (args.count == 0)
		do_ls(args);
	else
	{
		ft_lstsort(args.dirs_pre, 0, name_cmp);
		path = (t_path *)ft_memalloc(sizeof(t_path));
		while (args.dirs_pre)
		{
			gen_info(path, "", ((t_path *)args.dirs_pre->content)->filename);
			if (path->filename)
				ft_lst_add_back(&args.dirs, ft_lstnew(path, sizeof(t_path)));
			args.dirs_pre = args.dirs_pre->next;
		}
		ft_lstsort(args.dirs, args.r, args.t ? time_cmp : name_cmp);
		ft_lstsort(args.dirs, 0, dir_cmp);
		while (args.dirs)
		{
			x++;
			path = ((t_path *)(args.dirs->content));
			args.dir = path->filename;
			sym_is_dir = 0;
			if (stat(args.dir, &stats) != -1 && S_ISDIR(stats.st_mode))
				sym_is_dir = 1;
			if (args.count > 1 && (sym_is_dir || S_ISDIR(path->stats.st_mode)))
			{
				if (x > 0)
					ft_printf("\n");
				ft_printf("%s:\n", args.dir);
			}
			do_ls(args);
			args.dirs = args.dirs->next;
		}
	}
	return (0);
}
