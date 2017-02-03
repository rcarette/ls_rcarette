/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 07:49:08 by rcarette          #+#    #+#             */
/*   Updated: 2017/02/01 07:05:45 by rcarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

void			ft_count_arg(t_list *list, t_number *number)
{
	struct stat		inf;

	while (list)
	{
		if (lstat(list->value, &inf) == 0)
		{
			if (S_ISREG(inf.st_mode) || S_ISCHR(inf.st_mode)
				|| S_ISBLK(inf.st_mode) || S_ISLNK(inf.st_mode)
				|| S_ISSOCK(inf.st_mode) || S_ISFIFO(inf.st_mode))
				++number->files;
			else if (S_ISDIR(inf.st_mode))
			{
				list->valid = 1;
				++number->dir;
			}
		}
		else
		{
			list->valid = -1;
			++number->error;
		}
		list = list->next;
	}
}
