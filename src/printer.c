/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 20:01:02 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/03 16:52:04 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
	return (str);
}

void	print_file(t_args args, t_path *file, int widths[5])
{
	struct stat		stats;
	struct passwd	*pwd;
	struct group	*grp;

	if (args.l)
	{
		stats = file->stats;
		pwd = getpwuid(stats.st_uid);
		grp = getgrgid(stats.st_gid);
		print_permissions(file);
		ft_printf(" %*d %-*s %-*s ", widths[0], stats.st_nlink,
			widths[1], pwd->pw_name, widths[2], grp->gr_name);
		ft_printf(" %*lld %s ", widths[3], stats.st_size,
			time_string(stats.st_mtime));
	}
	if (S_ISLNK(stats.st_mode) && args.l)
		print_link(file, args);
	else
		ft_printf("%s\n", file->filename);
}

void	print_type(int mode)
{
	char		c;

	if (S_ISREG(mode))
		c = '-';
	else if (S_ISDIR(mode))
		c = 'd';
	else if (S_ISBLK(mode))
		c = 'b';
	else if (S_ISCHR(mode))
		c = 'c';
	else if (S_ISLNK(mode))
		c = 'l';
	else if (S_ISSOCK(mode))
		c = 's';
	else
		c = '-';
	ft_printf("%c", c);
}

void	print_permissions(t_path *file)
{
	int			mode;

	mode = file->stats.st_mode;
	print_type(mode);
	ft_printf((mode & S_IRUSR) ? "r" : "-");
	ft_printf((mode & S_IWUSR) ? "w" : "-");
	if (mode & S_ISUID)
		ft_printf((mode & S_IXUSR) ? "s" : "S");
	else
		ft_printf((mode & S_IXUSR) ? "x" : "-");
	ft_printf((mode & S_IRGRP) ? "r" : "-");
	ft_printf((mode & S_IWGRP) ? "w" : "-");
	if (mode & S_ISGID)
		ft_printf((mode & S_IXGRP) ? "s" : "S");
	else
		ft_printf((mode & S_IXGRP) ? "x" : "-");
	ft_printf((mode & S_IROTH) ? "r" : "-");
	ft_printf((mode & S_IWOTH) ? "w" : "-");
	if (mode & S_ISVTX)
		ft_printf((mode & S_IXUSR) ? "t" : "T");
	else
		ft_printf((mode & S_IXOTH) ? "x" : "-");
}

void	print_link(t_path *file, t_args args)
{
	char *tmp;
	char *sympath;

	if (ft_strequ(args.dir, file->filename))
		tmp = file->filename;
	else
		tmp = ft_strjoin(args.dir, file->filename);
	sympath = ft_strnew(PATH_MAX);
	readlink(tmp, sympath, PATH_MAX - 1);
	ft_printf("%s -> %s\n", file->filename, sympath);
	free(sympath);
}
