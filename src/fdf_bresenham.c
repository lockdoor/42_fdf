/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bresenham.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:38:19 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/09 12:02:00 by pnamnil          ###   ########.fr       */
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
	float temp = *x;
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
		// if (line->x_1 < 0)
		// 	fdf->offset_x = (int) fabs(line->x_1);
		// if (line->y_1 < 0)
		// 	fdf->offset_y = (int) fabs(line->y_1);
		line->x_1 += fdf->offset_x;
		line->y_1 += fdf->offset_y;
		line->x_2 += fdf->offset_x;
		line->y_2 += fdf->offset_y;
	}
}

int	gradient(t_fdf_line *line, int i)
{
	int start;
	int end;

	if (line->c_1)
		start = line->c_1;
	else if (line->z_1)
		start = 0xFFFF00;
	else
		start = 0xFFFFFF;
	if (line->c_2)
		end = line->c_2;
	else if (line->z_2)
		end = 0xFFFF00;
	else
		end = 0xFFFFFF;
	u_int8_t sr = start >> 16;
	u_int8_t sg = start >> 8;
	u_int8_t sb = start;
	u_int8_t er = end >> 16;
	u_int8_t eg = end >> 8;
	u_int8_t eb = end;

	float	st_r = (float)(er - sr) / line->step;
	float	st_g = (float)(eg - sg) / line->step;
	float	st_b = (float)(eb - sb) / line->step;
	
	u_int8_t rr = (sr + i * st_r);
	u_int8_t rg = (sg + i * st_g);
	u_int8_t rb = (sb + i * st_b);
	
	return (rr << 16 | rg << 8 | rb);
}

void	fdf_bresenham(t_fdf_line *line, t_fdf *fdf)
{
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
	int i = -1;
	// while ((int)(line->x_1 - line->x_2) || (int)(line->y_1 - line->y_2))
	while (++i < (int)line->step)
	{
		my_mlx_pixel_put(fdf, line->x_1, line->y_1, gradient(line, i + 1));
		line->x_1 += line->dx;
		line->y_1 += line->dy;
	}
}
