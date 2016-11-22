/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 09:07:30 by mhurd             #+#    #+#             */
/*   Updated: 2016/11/20 11:20:16 by mhurd            ###   ########.fr       */
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
	if (path->stats.st_mtimespec.tv_sec == next->stats.st_mtimespec.tv_sec)
	{
		if (path->stats.st_mtimespec.tv_nsec == next->stats.st_mtimespec.tv_nsec)
			return (name_cmp(path, next, order));
		if (order)
			return (path->stats.st_mtimespec.tv_nsec > next->stats.st_mtimespec.tv_nsec);
		else
			return (path->stats.st_mtimespec.tv_nsec < next->stats.st_mtimespec.tv_nsec);
	}
	if (order)
		return (path->stats.st_mtimespec.tv_sec > next->stats.st_mtimespec.tv_sec);
	else
		return (path->stats.st_mtimespec.tv_sec < next->stats.st_mtimespec.tv_sec);
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
