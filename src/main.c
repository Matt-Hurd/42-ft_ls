/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 15:35:03 by mhurd             #+#    #+#             */
/*   Updated: 2016/11/20 09:47:17 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	gen_info(t_path *dest, char *dir, char *filename)
{
	char	*tmp;

	tmp = ft_strjoin(dir, filename);
	if (lstat(tmp, &dest->stats) == -1)
	{
		printf("%s\n", tmp);
		printf("Error: %s\n", strerror(errno));
		exit(-1);
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
	widths[0] = 0;
	widths[1] = 0;
	widths[2] = 0;
	widths[3] = 0;
	widths[4] = 0;
	while (files)
	{
		struct stat stats = ((t_path *)files->content)->stats;
		widths[0] = MAX(num_len(stats.st_nlink), widths[0]);
		widths[1] = 5;
		widths[2] = 5;
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

char	*time_string(time_t t, int len)
{
	char *str;
	char *end;
	char **buff;
	char **buff2;

	buff = ft_strsplit(ft_strtrim(ctime(&t)), ' ');
	buff2 = ft_strsplit(buff[3], ':');
	if (year_length(t) == 4)
		asprintf(&end, "%s", buff[4]);
	else
		asprintf(&end, "%s:%s", buff2[0], buff2[1]);
	asprintf(&str, "%s %s %*s", buff[1], buff[2], len, end);
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

	char *owner = "mhurd";
	char *group = "july";
	if (args.l)
	{
		stats = file->stats;
		printf(S_ISDIR(stats.st_mode) ? "d" : "-");
		printf((stats.st_mode & S_IRUSR) ? "r" : "-");
		printf((stats.st_mode & S_IWUSR) ? "w" : "-");
		printf((stats.st_mode & S_IXUSR) ? "x" : "-");
		printf((stats.st_mode & S_IRGRP) ? "r" : "-");
		printf((stats.st_mode & S_IWGRP) ? "w" : "-");
		printf((stats.st_mode & S_IXGRP) ? "x" : "-");
		printf((stats.st_mode & S_IROTH) ? "r" : "-");
		printf((stats.st_mode & S_IWOTH) ? "w" : "-");
		printf((stats.st_mode & S_IXOTH) ? "x" : "-");
		printf(" %*d %*s %*s ", widths[0], stats.st_nlink, widths[1], owner, widths[2], group);
		printf(" %*lld %s ", widths[3], stats.st_size, time_string(stats.st_mtime, widths[4]));
	}
	printf("%s\n", file->filename);
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
	d = opendir(args.dir);
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
	set_widths(widths, files);
	blkcount = add_blocks(files);
	if (args.l)
		printf("total %lld\n", blkcount);
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
			if (S_ISDIR(((t_path *)iter->content)->stats.st_mode))
			{
				printf("\n");
				printf("%s%s:\n", current_dir, ((t_path *)iter->content)->filename);
				args.dir = ft_strjoin(current_dir, ((t_path *)iter->content)->filename);
				do_ls(args);
			}
			iter = iter->next;
		}
	}
}

int		main(int ac, char **av)
{
	t_args	args;

	clear_args(&args);
	process_args(ac, av, &args);
	do_ls(args);
	return (0);
}
