/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 13:36:52 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/07 11:40:58 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	fdf_set_color(t_fdf *fdf, int x, int y)
{
	if (fdf->data[y][x].color)
		return (fdf->data[y][x].color);
	else if (fdf->data[y][x].adj)
		return (0xFF0000);
	else
		return (0xFFFFFF);
}

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
	int	color;
			
	color = fdf_set_color (fdf, x, y);
	if (x < fdf->col - 1)
	{
		fdf_set_line (line, x, y, TRUE);
		fdf_bresenham (line, fdf, color);
	}
	if (y < fdf->row - 1)
	{
		fdf_set_line (line, x, y, FALSE);
		fdf_bresenham (line, fdf, color);
	}
}

void	fdf_draw_image(t_fdf *fdf)
{
	t_fdf_line	line;
	size_t		x;
	size_t		y;

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
}
