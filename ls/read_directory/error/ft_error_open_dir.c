/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_open_dir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 08:23:58 by rcarette          #+#    #+#             */
/*   Updated: 2017/01/07 13:54:12 by rcarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_ls.h"

void	ft_error_open_dir(char *name)
{
	ft_putstr("ft_ls: ");
	perror(name);
}

