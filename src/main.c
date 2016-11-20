/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 15:35:03 by mhurd             #+#    #+#             */
/*   Updated: 2016/11/20 07:50:16 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void swap(t_list *a, t_list *b)
{
    void *temp;

	temp = a->content;
    a->content = b->content;
    b->content = temp;
}

int		name_cmp(t_path *path, t_path *next, char order)
{
	int res;

	res = ft_strcmp(path->filename, next->filename);
	if (order)
		return (res < 0);
	else
		return (res > 0);
}

int		time_cmp(t_path *path, t_path *next, char order)
{
	if (path->stats.st_mtime == next->stats.st_mtime)
		return (name_cmp(path, next, order));
	if (order)
		return (path->stats.st_mtime > next->stats.st_mtime);
	else
		return (path->stats.st_mtime < next->stats.st_mtime);
}

void ft_lstsort(t_list *start, char order, int (*f)(t_path *, t_path *, char))
{
    int swapped;
	int i;
    t_list *ptr1;
    t_list *lptr;

	lptr = NULL;
    if (start == NULL)
        return;
	swapped = 1;
	while (swapped)
	{
        swapped = 0;
        ptr1 = start;
        while (ptr1->next != lptr)
        {
            if (f(ptr1->content, ptr1->next->content, order))
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
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
				if (av[count][iter] == 'l')
					args->l = 1;
				else if (av[count][iter] == 'R')
					args->R = 1;
				else if (av[count][iter] == 'r')
					args->r = 1;
				else if (av[count][iter] == 'a')
					args->a = 1;
				else if (av[count][iter] == 't')
					args->t = 1;
				else if (av[count][iter] == 'f')
					args->f = 1;
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

void	set_widths(int widths[5], t_list *files)
{
	while (files)
	{
		struct stat stats = ((t_path *)files->content)->stats;
		widths[0] = MAX(num_len(stats.st_nlink), widths[0]);
		widths[1] = 5;
		widths[2] = 5;
		widths[3] = MAX(num_len(stats.st_size), widths[3]);
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

int		main(int ac, char **av)
{
	struct	dirent *dir;
	DIR		*d;
	t_list	*files;
	int		count;
	t_args	args;
	t_path	path;
	int		widths[5];

	clear_args(&args);
	process_args(ac, av, &args);
	files = 0;
	// printf("l%d, R%d, r%d, a%d, t%d, %s\n", args.l, args.R, args.r, args.a, args.t, args.dir);
	count = 0;
	args.dir = ft_strjoin(args.dir ? args.dir : ".", "/");
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
	unsigned int st_mode;
	set_widths(widths, files);
	char *owner = "mhurd";
	char *group = "july";
	char *date = "Nov 20 03:59";
	while (files)
	{
		if (args.l)
		{
			struct stat stats = ((t_path *)files->content)->stats;
			printf(S_ISDIR(stats.st_mode ) ? "d" : "-");
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
			printf(" %*lld %s ", widths[3], stats.st_size, date);
		}
		printf("%s\n", ((t_path *)files->content)->filename);
		files = files->next;
	}
	return (0);
}
