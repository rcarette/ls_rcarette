/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 12:59:59 by rcarette          #+#    #+#             */
/*   Updated: 2017/02/03 05:50:06 by rcarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/ioctl.h>

t_list			*creat_list(t_list *li, int choice)
{
	t_list		*new_list;
	t_data		*data;

	new_list = NULL;
	while (li)
	{
		if (li->valid == choice)
		{
			ft_init_data(&data, li->value, li->date_value, li->size_value);
			push_data(&new_list, data);
		}
		li = li->next;
	}
	return (new_list);
}

void			ft_start_ls(t_list **list, t_opt opt)
{
	t_number	number;
	t_list		*new_list;
	t_list		*temporary;
	
	new_list = NULL;
	number = ft_initialization_number();
	ft_count_arg(*list, &number);
	(number.error > 0) ? ft_display_error(*list) : 0;
	new_list = creat_list(*list, 0);
	(number.files > 0) ? ft_display_files(&new_list, opt, number) : 0;
	ft_clear_list(&new_list);
	new_list = NULL;
	if (number.dir > 0 && (number.error > 0 || number.files > 0))
		write(1, "\n", 1);
	new_list = creat_list(*list, 1);
	ft_clear_list(list);
	ft_tri_bulle_dlist_sort_ascii(&new_list);
	(opt.date_sort) ? ft_tri_bulle_dlist_sort_time(&new_list) : 0;
	(opt.reverse) ? ft_list_reverse(&new_list) : 0;
	(number.dir >= 1) ? ft_start_read_directory(&new_list, opt, number) : 0;
}

int				main(int argc, char *argv[])
{
	t_opt				opt;
	t_list				*li;
	t_data				*data;

	li = new_list();
	opt = ft_initialization_opt();
	if (argc == 1 || (argc >= 2 && ft_strcmp(argv[1], "--") == 0)
					|| (argc >= 2 && argv[1][0] != '-'))
		creat_param(&li, argc, argv);
	else
	{
		ft_parsing_ls(argc, argv, &opt);
		if (!opt.i_param)
		{
			ft_init_data(&data, ".", 0, 2);
			push_data(&li, data);
			free(data);
		}
		else
			creat_param_via_i_param(argc, argv, opt, &li);
	}
	ft_tri_bulle_dlist_sort_ascii(&li);
	ft_start_ls(&li, opt);
	return (0);
}
