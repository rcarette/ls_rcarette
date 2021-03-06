/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 15:17:36 by rcarette          #+#    #+#             */
/*   Updated: 2017/02/03 17:04:22 by rcarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_ls.h"

int		ft_count(t_list *new_list)
{
	char	*str;
	int		size;

	size = 0;
	while (new_list)
	{
		str = ft_strrchr(new_list->value, '/');
		++str;
		if (ft_strlen(str) >= size)
			size = (ft_strlen(str) + 1);
		new_list = new_list->next;
	}
	return (size);
}

void	ft_read_file(t_list *list, int size_term, t_opt opt)
{
	char			*str;
	int				i;
	int				x;
	int				size;
	struct stat		inf;

	i = 0;
	size = ft_count(list);
	x = (size_term / size);
	while (list)
	{
		lstat(list->value, &inf);
		str = ft_strrchr(list->value, '/');
		ft_print_color(inf);
		ft_putstr(++str);
		write(1, "\033[0;0m", ft_strlen("\033[0;0m"));
		if (++i != size)
			if (list->next != NULL)
				ft_print_n(size, ft_strlen(str));
		if (list->next == NULL)
			break;
		if (i == x)
		{
			ft_putchar('\n');
			i = 0;
		}
		list = list->next;
	}
}

void	ft_display_one(t_list *list)
{
	char	*str;

	while (list)
	{
		str = ft_strrchr(list->value, '/');
		ft_putendl(++str);
		list = list->next;
	}
}
