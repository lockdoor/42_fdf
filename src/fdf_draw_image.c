/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 13:36:52 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/09 11:11:58 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_set_line(t_fdf_line *line, int x, int y, t_bool mode)
{
	line->x_1 = x;
	line->y_1 = y;
	line->x_2 = x;
	line->y_2 = y;
	if (mode)
		line->x_2 += 1;
	else
		line->y_2 += 1;
}

static void	fdf_draw(t_fdf *fdf, t_fdf_line *line, int x, int y)
{
	if (x < (int)fdf->col - 1)
	{
		fdf_set_line (line, x, y, TRUE);
		fdf_bresenham (line, fdf);
	}
	if (y < (int)fdf->row - 1)
	{
		fdf_set_line (line, x, y, FALSE);
		fdf_bresenham (line, fdf);
	}
}

void	fdf_draw_image(t_fdf *fdf)
{
	t_fdf_line	line;
	size_t		x;
	size_t		y;

	ft_bzero (fdf->addr, fdf->width * fdf->height * (fdf->bpp / 8));
	y = 0;
	while (y < fdf->row)
	{
		x = 0;
		while (x < fdf->col)
		{
			fdf_draw (fdf, &line, x, y);
			x++ ;
		}
		y++ ;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, fdf->menu_x, 0);
}
