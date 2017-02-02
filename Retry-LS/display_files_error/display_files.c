/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 07:34:08 by rcarette          #+#    #+#             */
/*   Updated: 2017/02/02 05:00:55 by rcarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

void	display_opt_one(t_list *list)
{
	while (list)
	{
		(list->valid == 0) ? write(1, list->value, list->size_value) : 0;
		(list->valid == 0) ? write(1, "\n", 1) : 0;
		list = list->next;
	}
}

void	display_default(t_list *t, int nbr_file, int space)
{
	while (t)
	{
		(t->valid == 0) ? write(1, t->value, t->size_value) : 0;
		if (t->valid == 0 && nbr_file > 0)
		{
			--nbr_file;
			ft_print_n(space, ft_strlen(t->value));
		}
		t = t->next;
	}
}

char	*ft_get_name(long int x)
{
	struct passwd	*pass;

	pass = getpwuid(x);
	return (pass->pw_name);
}

char	*ft_get_group(long int x)
{
	struct group	*grp;

	grp = getgrgid(x);
	return (grp->gr_name);
}

void	get_infos_file(t_list *t, t_info *infos)
{
	struct stat		inf;
	size_t			size;

	init_t_info(infos);
	while (t)
	{
		stat(t->value, &inf);
		size = ft_strlen(ft_get_name(inf.st_uid));
		if (size > infos->size_name)
			infos->size_name = size;
		size = ft_strlen(ft_get_group(inf.st_gid));
		if (infos->size_group < size)
			infos->size_group = size;
		t = t->next;
	}
}

void	display_listing(t_list *list, int file)
{
	struct stat		inf;
	t_list			*t;
	t_info			infos;

	t = list;
	get_infos_file(t, &infos);
	printf("%d\n", infos.size_name);
	printf("%d\n", infos.size_group);
}

void	ft_display_files(t_list **list, t_opt opt, t_number number)
{
	int			space;
	t_list		*t;
	int			files;

	files = number.files;
	space = ft_count_character(*list);
	(opt.date_sort) ? ft_tri_bulle_dlist_sort_time(list) : 0;
	(opt.reverse) ? ft_list_reverse(list) : 0;
	t = *list;
	if (opt.opt_one == 1 && opt.listing == 0)
	{
		display_opt_one(t);
		return ;
	}
	else if (opt.listing == 1)
		display_listing(t, files);
	else
		display_default(t, files, space);
	(opt.listing == 0) ? ft_putchar('\n') : 0;
}
