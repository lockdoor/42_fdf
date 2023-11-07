/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bresenham.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:38:19 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/07 11:39:16 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	dst = fdf->addr + (y * fdf->line_length + x * (fdf->bpp / 8));
	*(unsigned int *) dst = color;
}

static void	fdf_isometric(float *x, float *y, int z, float angle)
{
	*x = (*x - *y) * cos(angle);
	*y = ((*x + *y) * sin(angle)) - z;
}

static void	fdf_zoom(t_fdf_line *line, t_fdf *fdf)
{
	line->x_1 *= fdf->zoom;
	line->y_1 *= fdf->zoom;
	line->x_2 *= fdf->zoom;
	line->y_2 *= fdf->zoom;
}

static void	fdf_shift(t_fdf_line *line, t_fdf *fdf)
{
	line->x_1 += fdf->shift;
	line->y_1 += fdf->shift;
	line->x_2 += fdf->shift;
	line->y_2 += fdf->shift;
}

void	fdf_bresenham(t_fdf_line *line, t_fdf *fdf, int color)
{
	int	z_1;
	int	z_2;

	z_1 = fdf->data[(int)line->y_1][(int)line->x_1].adj;
	z_2 = fdf->data[(int)line->y_2][(int)line->x_2].adj;
	fdf_zoom (line, fdf);
	fdf_isometric (&line->x_1, &line->y_1, z_1, 1);
	fdf_isometric (&line->x_2, &line->y_2, z_2, 1);
	fdf_shift(line, fdf);
	line->dx = line->x_2 - line->x_1;
	line->dy = line->y_2 - line->y_1;
	line->step = (int) fmax (fabs(line->dx), fabs(line->dy));
	line->dx /= line->step;
	line->dy /= line->step;
	while ((int)(line->x_1 - line->x_2) || (int)(line->y_1 - line->y_2))
	{
		my_mlx_pixel_put(fdf, round(line->x_1),
			round(line->y_1), color);
		line->x_1 += line->dx;
		line->y_1 += line->dy;
	}
}
