/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:14:40 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/04 16:42:19 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	dst = fdf->addr + (y * fdf->line_length + x * (fdf->bpp / 8));
	*(unsigned int*)dst = color;
}

void draw_line_dda (int x_1, int y_1, int x_2, int y_2, t_fdf *fdf, int color)
{
	float	x, y, step, dx, dy;

	dx = (x_2 - x_1) * 20; //10
	dy = (y_2 - y_1) * 20; //9
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

void	draw_image (t_fdf *fdf)
{
	size_t	col;
	size_t	row;

	row = 0;
	while (row < fdf->row)
	{
		col = 0;
		while (col < fdf->col)
		{
			draw_line_dda (col, row, col, row + 1, fdf, 0xFFFFFFFF);
			draw_line_dda (col, row, col + 1, row, fdf, 0xFFFFFFFF);

			col++ ;
		}
		row++ ;
	}
}

int	main(int argc, char **argv)
{
	// void	*mlx;
	t_fdf	fdf;

	// check number of argument
	if (argc != 2)
		fdf_exit_error (INVALID_ARG, EXIT_FAILURE);

	// read file
	ft_bzero (&fdf, sizeof(fdf));
	fdf.pname = argv[0];
	fdf.filename = argv[1];
	fdf_read_file (&fdf);
	fdf.mlx = mlx_init();
	fdf.mlx_win = mlx_new_window(fdf.mlx, 400, 400, fdf.filename);
	fdf.img = mlx_new_image(fdf.mlx, 400, 400);
	fdf.addr = mlx_get_data_addr(fdf.img, &fdf.bpp, &fdf.line_length, &fdf.endian);

	// my_mlx_pixel_put(&fdf, 200, 200, 0xFFFFFFFF);
	draw_image (&fdf);
	mlx_put_image_to_window(fdf.mlx, fdf.mlx_win, fdf.img, 0, 0);
	mlx_loop(fdf.mlx);
	
	return (0);
}