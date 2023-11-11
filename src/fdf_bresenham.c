/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bresenham.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:38:19 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/11 09:46:31 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* fdf->bpp = 32, 32 bit RGBA color */
static void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= (int)fdf->width || y < 0 || y >= (int)fdf->height)
		return ;
	dst = fdf->addr + (y * fdf->line_length + x * (fdf->bpp / 8));
	*(unsigned int *) dst = color;
}

/* default */
// static void	fdf_isometric(float *x, float *y, int z, float angle)
// {
// 	*x = (*x - *y) * cos(angle);
// 	*y = ((*x + *y) * sin(angle)) - z;
// }

static void	fdf_isometric(float *x, float *y, int z, float angle)
{
	float	temp;

	temp = *x;
	*x = (*x - *y) * cos(angle);
	*y = ((temp + *y) * sin(angle)) - z;
}

// static void	fdf_isometric(float *x, float *y, int z, float angle)
// {
// 	float temp = *y;
// 	*y = (*y - *x) * cos(angle);
// 	*x = ((temp + *x) * sin(angle)) - z;
// }

static void	fdf_zoom(t_fdf_line *line, t_fdf *fdf)
{
	line->x_1 *= fdf->zoom;
	line->y_1 *= fdf->zoom;
	line->x_2 *= fdf->zoom;
	line->y_2 *= fdf->zoom;
}

static void	fdf_offset(t_fdf_line *line, t_fdf *fdf)
{
	if (fdf->isometric)
	{
		line->x_1 += fdf->offset_x;
		line->y_1 += fdf->offset_y;
		line->x_2 += fdf->offset_x;
		line->y_2 += fdf->offset_y;
	}
}

void	fdf_bresenham(t_fdf_line *line, t_fdf *fdf)
{
	int	i;

	line->z_1 = fdf->data[(int)line->y_1][(int)line->x_1].adj * fdf->adj;
	line->z_2 = fdf->data[(int)line->y_2][(int)line->x_2].adj * fdf->adj;
	line->c_1 = fdf->data[(int)line->y_1][(int)line->x_1].color;
	line->c_2 = fdf->data[(int)line->y_2][(int)line->x_2].color;
	fdf_zoom (line, fdf);
	if (fdf->isometric)
	{
		fdf_isometric (&line->x_1, &line->y_1, line->z_1, fdf->angle);
		fdf_isometric (&line->x_2, &line->y_2, line->z_2, fdf->angle);
	}
	fdf_offset (line, fdf);
	line->dx = line->x_2 - line->x_1;
	line->dy = line->y_2 - line->y_1;
	line->step = fmax (fabs(line->dx), fabs(line->dy));
	line->dx /= line->step;
	line->dy /= line->step;
	i = -1;
	while (++i < (int)line->step)
	{
		my_mlx_pixel_put(fdf, line->x_1, line->y_1, fdf_gradient(line, i + 1));
		line->x_1 += line->dx;
		line->y_1 += line->dy;
	}
}
