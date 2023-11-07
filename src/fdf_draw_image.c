/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 13:36:52 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/06 16:56:51 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	dst = fdf->addr + (y * fdf->line_length + x * (fdf->bpp / 8));
	*(unsigned int*)dst = color;
}

void	isometric(float *x, float *y, int z, float angle)
{
	*x = (*x - *y) * cos(angle);
	*y = ((*x + *y) * sin(angle)) - z;
}

static void draw_line_dda (t_fdf_line *line, t_fdf *fdf, int color)
{
	// size_t	i;

	/* data */
	int		z;
	// int		z1;
	z = (int)(line->y_1 * fdf->col) + (int)line->x_1;
	z = fdf->data[z].adj;
	// z1 = fdf->data[(int)(line->y_2 * line->x_2)].adj;
	

	/* zoom */
	line->x_1 *= fdf->zoom;
	line->y_1 *= fdf->zoom;
	line->x_2 *= fdf->zoom;
	line->y_2 *= fdf->zoom;

	/* 3D */
	isometric (&line->x_1, &line->y_1, z, 0.8);
	isometric (&line->x_2, &line->y_2, z, 0.8);

	/* shift */
	line->x_1 += 150;
	line->y_1 += 150;
	line->x_2 += 150;
	line->y_2 += 150;

	line->dx = line->x_2 - line->x_1;
	line->dy = line->y_2 - line->y_1;
	line->step = (int) fmax (line->dx, line->dy);
	line->dx /= line->step;
	line->dy /= line->step;
	// i = 0;
	// while (i <= line->step)
	while ((int)(line->x_1 - line->x_2) || (int)(line->y_1 - line->y_2))
	{
		my_mlx_pixel_put(fdf, round(line->x_1),
			round(line->y_1), color);
		// mlx_pixel_put(fdf->mlx, fdf->win, line->x_1, line->x_2, color);
		line->x_1 += line->dx;
		line->y_1 += line->dy;
		// i++ ;
	}
}

void	fdf_draw_image (t_fdf *fdf)
{
	t_fdf_line	line;
	size_t		x;
	size_t		y;
	int			color;

	y = 0;
	fdf->zoom = 20;
	while (y < fdf->row)
	{
		x = 0;
		while (x < fdf->col)
		{
			if (fdf->data[y * fdf->col + x].color)
				color = fdf->data[y * fdf->col + x].color;
			else if (fdf->data[y * fdf->col + x].adj)
				color = 0xFF0000;
			else
				color = 0xFFFFFF;
			if (x < fdf->col - 1)
			{
				line.x_1 = x;
				line.y_1 = y;
				line.x_2 = x + 1;
				line.y_2 = y;
				draw_line_dda (&line, fdf, color);
			}
			if (y < fdf->row - 1)
			{
				line.x_1 = x;
				line.y_1 = y;
				line.x_2 = x;
				line.y_2 = y + 1;
				draw_line_dda (&line, fdf, color);		
			}
			x++ ;
		}
		y++ ;
	}
}

/*
static void draw_line_dda (int x_1, int y_1, int x_2, int y_2, t_fdf *fdf, int color)
{
	float	x, y, step, dx, dy;

	dx = x_2 - x_1; //10
	dy = y_2 - y_1; //9
	if (fabsf(dx) >= fabsf(dy))
		step = fabsf (dx);
	else
		step = fabsf (dy);
	dx = dx / step;
	dy = dy / step;
	x = x_1;
	y = y_1;
	for (int i = 0; i <= step; i++)
	{
		my_mlx_pixel_put(fdf, round(x), round(y), color);
		x = x + dx;
		y = y + dy;
	}
}
*/

/*
void	fdf_draw_image (t_fdf *fdf)
{
	size_t	col;
	size_t	row;
	size_t	zoom;

	row = 0;
	zoom = 20;
	while (row < fdf->row)
	{
		col = 0;
		while (col < fdf->col)
		{
			if ()
			draw_line_dda (col * zoom, row * zoom, col * zoom, row * zoom + zoom, fdf, 0xFFFFFFFF);
			draw_line_dda (col * zoom, row * zoom, col * zoom + zoom, row * zoom, fdf, 0xFFFFFFFF);
			col++ ;
		}
		draw_line_dda (col * zoom, row * zoom, col * zoom, row * zoom + zoom, fdf, 0xFFFFFFFF);
		row++ ;
	}
	col = 0;
	while (col < fdf->col)
	{
		draw_line_dda (col * zoom, row * zoom, col * zoom + zoom, row * zoom, fdf, 0xFFFFFFFF);
		col++ ;
	}
}
*/
