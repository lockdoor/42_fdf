/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 13:36:52 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/05 15:16:25 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct s_fdf_line
{
	int		x_1;
	int		y_1;
	int		x_2;
	int		y_2;
	float	dx;
	float	dy;
	// float	y;
	// float	x;
	float	step;
}	t_fdf_line;

static void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	dst = fdf->addr + (y * fdf->line_length + x * (fdf->bpp / 8));
	*(unsigned int*)dst = color;
}

static void draw_line_dda (t_fdf_line *line, t_fdf *fdf, int color)
{
	line->dx = line->x_2 - line->x_1;
	line->dy = line->y_2 - line->y_1;
	if (fabsf(line->dx) >= fabsf(line->dy))
		line->step = fabsf (line->dx);
	else
		line->step = fabsf (line->dy);
	line->dx = line->dx / line->step;
	line->dy = line->dy / line->step;
	// line->x = line->x_1;
	// line->y = line->y_1;
	for (int i = 0; i <= line->step; i++)
	{
		my_mlx_pixel_put(fdf, round(line->x), round(line->y), color);
		line->x_1 = line->x_1 + line->dx;
		line->y_1 = line->y_1 + line->dy;
	}
}



void	fdf_draw_image (t_fdf *fdf)
{
	t_fdf_line	line;
	size_t		x;
	size_t		y;

	y = 0;
	fdf->zoom = 20;
	while (y < fdf->row)
	{
		x = 0;
		while (x < fdf->col)
		{
			line.x_1 = x * fdf->zoom;
			line.y_1 = y * fdf->zoom;
			line.x_2 = line.x_1 + fdf->zoom;
			line.y_2 = line.y_1;
			draw_line_dda (&line, fdf, 0xFFFFFFFF);
			line.x_2 = line.x_1;
			line.y_2 = line.y_1 + fdf->zoom;
			draw_line_dda (&line, fdf, 0xFFFFFFFF);
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
