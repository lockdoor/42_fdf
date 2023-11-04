/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:55:47 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/03 15:57:32 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_split(char **split)
{
	while (*split)
	{
		ft_printf ("%3s", *split++);
	}
	ft_printf ("\n");
}

void	print_data_debug(t_fdf *fdf)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < fdf->data_row)
	{
		j = 0;
		while (j < fdf->data_col)
		{
			ft_printf ("%3d", fdf->data[(i * fdf->data_col) + j][0]);
			j++ ;
		}
		ft_printf ("\n");
		i++ ;
	}
}
