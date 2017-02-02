/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 14:02:24 by rcarette          #+#    #+#             */
/*   Updated: 2017/02/01 08:17:17 by rcarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int			ft_error_flags(char *character, int i)
{
	ft_putstr("ft_ls: illegal option -- ");
	if (i == 0)
		write(1, character, ft_strlen(character));
	else
		write(1, character, 1);
	ft_putchar('\n');
	ft_putendl("usage: ls [-altrR1F] [--all] - [file ...]");
	exit(0);
}

int		if_flags(char character, char *flag)
{
	int		i;

	i = -1;
	while (flag[++i])
		if (character == flag[i])
			return (0);
	return (1);
}

static void			check_flags(t_opt *opt, char *str)
{
	int		i;

	i = 0;
	if (str[i] == '-' && str[i + 1] == '-')
		opt->file_hide = (ft_strcmp(str, "--all")) ? ft_error_flags(str, 1) : 1;
	else
		while (str[++i])
		{
			opt->reverse = (str[i] == 'r') ? 1 : 0;
			opt->upper_r = (str[i] == 'R') ? 1 : 0;
			opt->listing = (str[i] == 'l') ? 1 : 0;
			opt->date_sort = (str[i] == 't') ? 1 : 0;
			opt->file_hide = (str[i] == 'a') ? 1 : 0;
			opt->opt_one = (str[i] == '1') ? 1 : 0;
			opt->add_ff = (str[i] == 'F') ? 1 : 0;
			(if_flags(str[i], "rRlta1F")) ? ft_error_flags(&str[i], 1) : 0;
			opt->number_opt++;
		}
}

void				ft_parsing_ls(int ac, char **av, t_opt *opt)
{
	int		i;

	i = 0;
	while (++i < ac)
	{
		if (ft_strcmp(av[i], "--") == 0 && av[i + 1] != NULL)
		{
			opt->i_param = ++i;
			return ;
		}
		else if (ft_strcmp(av[i], "--") == 0 && i != ac)
		{
			opt->i_param = 0;
			return ;
		}
		else if (av[i][0] == '-')
			check_flags(opt, av[i]);
		else if (av[i][0] != '-')
		{
			opt->i_param = i;
			return ;
		}
	}
}

void				creat_param(t_list **li, int ac, char **av)
{
	t_data			*data;
	int				i;
	struct stat		infos;

	i = 0;
	if (ac == 1 || (ft_strcmp(av[1], "--") == 0 && ac == 2))
	{
		ft_init_data(&data, ".", 0, 2);
		push_data(li, data);
		free(data->value);
		free(data);
		return ;
	}
	((ft_strcmp(av[1], "--")) == 0) ? ++i : 0;
	while (++i < ac)
	{
		stat(av[i], &infos);
		ft_init_data(&data, av[i], infos.st_mtime, (ft_strlen(av[i]) + 1));
		push_data(li, data);
		ft_free_data(&data);
	}
}

void				creat_param_via_i_param(int ac, char **av, t_opt opt,
		t_list **li)
{
	t_data			*data;
	struct stat		infos;

	while (opt.i_param < ac)
	{
		(opt.listing) ? lstat(av[opt.i_param], &infos) :
			stat(av[opt.i_param], &infos);
		ft_init_data(&data, av[opt.i_param], infos.st_mtime,
				(ft_strlen(av[opt.i_param]) + 1));
		push_data(li, data);
		ft_free_data(&data);
		++opt.i_param;
	}
}
