/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 07:34:08 by rcarette          #+#    #+#             */
/*   Updated: 2017/02/03 16:55:49 by rcarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

void	manage_buffer(char character, char buffer[2048])
{
	int		i;

	i = -1;
	while (buffer[++i])
		;
	buffer[i] = character;
}

void	ft_get_symbolique(char *name, t_opt opt)
{
	char	tab[256];

	ft_memset(tab, '\0', 256);
	if (readlink(name, tab, 256) != -1)
	{
		write(1, " -> ", 4);
		write(1, tab, ft_strlen(tab));
	}
		ft_memset(tab, '\0', 256);
}
void	write_mode(long int x)
{
	ft_putchar((S_ISFIFO(x)) ? 'p' : 0);
	ft_putchar((S_ISCHR(x)) ? 'c' : 0);
	ft_putchar((S_ISDIR(x)) ? 'd' : 0);
	ft_putchar((S_ISBLK(x)) ? 'b' : 0);
	ft_putchar((S_ISREG(x)) ? '-' : 0);
	ft_putchar((S_ISLNK(x)) ? 'l' : 0);
	ft_putchar((S_ISSOCK(x)) ? 's' : 0);
	ft_putstr((x & S_IRUSR) ? "r" : "-");
	ft_putstr((x & S_IWUSR) ? "w" : "-");
	if ((S_ISUID & x))
		ft_putchar((S_IXUSR & x) ? 's' : 'S');
	else
		ft_putstr((x & S_IXUSR) ? "x" : "-");
	ft_putstr((x & S_IRGRP) ? "r" : "-");
	ft_putstr((x & S_IWGRP) ? "w" : "-");
	if (S_ISGID & x)
		ft_putchar((S_IXGRP & x) ? 's' : 'S');
	else
		ft_putstr((x & S_IXGRP) ? "x" : "-");
	ft_putstr((x & S_IROTH) ? "r" : "-");
	ft_putstr((x & S_IWOTH) ? "w" : "-");
	if (S_ISVTX & x)
		ft_putchar((S_IXOTH & x) ? 't' : 'T');
	else
		ft_putstr((x & S_IXOTH) ? "x" : "-");
}

void	display_opt_one(t_list *list, t_opt opt)
{
	struct stat		inf;
	while (list)
	{
		lstat(list->value, &inf);
		(opt.color == 1) ? ft_print_color(inf) : 0;
		write(1, list->value, list->size_value);
		write(1, "\033[0;0m", ft_strlen("\033[0;0m"));
		write(1, "\n", 1);
		list = list->next;
	}
}

void	display_default(t_list *t, int nbr_file, int space, t_opt opt)
{
	struct stat		inf;
	while (t)
	{
		lstat(t->value, &inf);
		(opt.color == 1) ? ft_print_color(inf) : 0;
		(t->valid == 0) ? write(1, t->value, t->size_value) : 0;
		write(1, "\033[0;0m", ft_strlen("\033[0;0m"));
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

char	*ft_get_link(long int x)
{
	return (ft_itoa(x));
}

void	print_x_characters(int nbr)
{
	int		i;

	i = -1;
	if (nbr <= 0)
		return ;
	while (++i < nbr)
		write(1, " ", 1);
}

void	get_infos_file(t_list *t, t_info *infos)
{
	struct stat		inf;
	size_t			size;
	char			*temporary;

	init_t_info(infos);
	while (t)
	{
		lstat(t->value, &inf);
		size = ft_strlen((temporary = ft_itoa(inf.st_size)));
		if (size > infos->size_octets)
			infos->size_octets = size;
		free(temporary);
		size = ft_strlen((temporary = ft_itoa(inf.st_nlink)));
		if (size > infos->size_link)
			infos->size_link = size;
		free(temporary);
		temporary = ft_get_name(inf.st_uid);
		if ((size = ft_strlen(temporary)) > infos->size_name)
			infos->size_name = size;
		temporary = ft_get_group(inf.st_gid);
		if ((size = ft_strlen(temporary)) > infos->size_group)
			infos->size_group = size;
		t = t->next;
	}
}

void	ft_get_date(struct stat inf, time_t date, char *dated)
{
	time_t		now;
	char		*t;
	char		*i;

	now = time(NULL);
	now -= date;
	if (now < 15778800)
	{
		t = ft_strsub(dated, 4, 12);
		write(1, t, ft_strlen(t));
		free(t);
	}
	else
	{
		write(1, dated + 4, 7);
		write(1, dated + 20, 4);
	}
	write(1, " ", 1);
}

void	write_link(long int link, t_info *inf)
{
	char	*nlink;
	int		size;

	nlink = ft_itoa(link);
	if ((size = ft_strlen(nlink)) < inf->size_link)
		print_x_characters((inf->size_link - size));
	write(1, nlink, size);
	write(1, " ", 1);
}

void	write_name(char *name, t_info *inf)
{
	int		size;

	size = ft_strlen(name);
	write(1, name, size);
	if (size < inf->size_name)
	{
		size = ((inf->size_name - size));
		print_x_characters(size);
	}
	write(1, "  ", 2);
}

void	write_group(char *group, t_info *inf)
{
	int		size;

	size = ft_strlen(group);
	write(1, group, size);
	print_x_characters(inf->size_group - size);
}

void	get_infos_minor_major(t_list *t, t_info *info)
{
	struct stat		inf;
	int				size;
	char			*recup;

	while (t)
	{
		lstat(t->value, &inf);
		if (S_ISCHR(inf.st_mode) || S_ISBLK(inf.st_mode))
		{
			info->minor_major = 1;
			size = ft_strlen((recup = ft_itoa(major(inf.st_rdev))));
			if (size > info->size_major)
				info->size_major = size;
			free(recup);
			size = ft_strlen((recup = ft_itoa(minor(inf.st_rdev))));
			if (size > info->size_minor)
				info->size_minor = size;
			free(recup);
		}
		t = t->next;
	}
}

void	write_minor_major(char *major, char *minor, t_info *info)
{
	int		size;

	size = ft_strlen(major);
	if (info->size_major == 1)
		write(1, " ", 1);
	write(1, "   ", 3);
	print_x_characters(info->size_major - size);
	write(1, major, size);
	write(1, ",", 1);
	size = ft_strlen(minor);
	(size == 1) ? write(1, "   ", 3) : 0;
	(size == 2) ? write(1, "  ", 2) : 0;
	(size == 3) ? write(1, " ", 1) : 0;
	write(1, minor, size);
	write(1, " ", 1);
}

void	write_octet(char *octets, t_info *info)
{
	int		size;

	size = ft_strlen(octets);
	if (info->minor_major == 1)
	{
		print_x_characters(info->size_group - size);
		write(1, octets, size);
	}
	else
	{
		write(1, "  ", 2);
		if (size < info->size_octets)
			print_x_characters(info->size_octets - size);
		write(1, octets, size);
	}
	write(1, " ", 1);
}

void	ft_print_color(struct stat inf)
{
	if (S_ISBLK(inf.st_mode))
		write(1, "\033[46;34m", ft_strlen("\033[46;34m"));
	else if (S_ISLNK(inf.st_mode))
		write(1, "\033[35m", 5);
	else if (S_ISDIR(inf.st_mode))
		write(1, "\033[36;1m", ft_strlen("\033[36;1m"));
	else if (inf.st_mode & S_IXUSR && inf.st_mode & S_IXGRP
			&& inf.st_mode & S_IXOTH)
		write(1, "\033[31m", 5);
	else if (S_ISCHR(inf.st_mode))
		write(1, "\033[43;34m", ft_strlen("\033[43;34m"));
}

void	ft_write_name(char *name, struct stat inf, int choice, t_opt opt)
{
	char	*temporary;

	(opt.color == 1) ? ft_print_color(inf) : 0;
	if (choice == 1)
		write(1, name, ft_strlen(name));
	else
	{
		temporary = ft_strrchr(name, '/');
		++temporary;
		write(1, temporary, ft_strlen(temporary));
	}
	write(1, "\033[0;0m", ft_strlen("\033[0;0m"));
	if (S_ISLNK(inf.st_mode))
		ft_get_symbolique(name, opt);
}

void	display_listing(t_list *list, t_opt opt, int choice)
{
	struct stat		inf;
	t_list			*t;
	t_info			infos;

	t = list;
	get_infos_file(t, &infos);
	get_infos_minor_major(t, &infos);
	while (list)
	{
		lstat(list->value, &inf);
		write_mode(inf.st_mode);
		write(1, "  ", 2);
		write_link(inf.st_nlink, &infos);
		write_name(ft_get_name(inf.st_uid), &infos);
		write_group(ft_get_group(inf.st_gid), &infos);
		if (S_ISCHR(inf.st_mode) || S_ISBLK(inf.st_mode))
			write_minor_major(ft_itoa(major(inf.st_rdev)),
					ft_itoa(minor(inf.st_rdev)), &infos);
		else
			write_octet(ft_itoa(inf.st_size), &infos);
		ft_get_date(inf, inf.st_mtime, ctime(&inf.st_mtime));
		ft_write_name(list->value, inf, choice, opt);
		(list->next != NULL) ? write(1, "\n", 1) : 0;
		list = list->next;
	}
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
		display_opt_one(t, opt);
		return ;
	}
	else if (opt.listing == 1)
		display_listing(t, opt, 1);
	else
		display_default(t, files, space, opt);
	write(1, "\n", 1);
}
