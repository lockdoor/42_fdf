/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 06:22:25 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/03 10:14:10 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"



// int	main(void)
// {
// 	void	*mlx;

// 	mlx = mlx_init();
// }


// int	main(void)
// {
// 	void	*mlx;
// 	void	*mlx_win;

// 	mlx = mlx_init();
// 	mlx_win = mlx_new_window(mlx, 400, 400, "Hello world!");
// 	mlx_loop(mlx);
// }

void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	dst = fdf->addr + (y * fdf->line_length + x * (fdf->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	write_squre(t_data *img, int w)
{
	for (int i = 0; i < w; i++){
		my_mlx_pixel_put(img, i, 0, 0x0000FF00);
		my_mlx_pixel_put(img, i, w, 0x0000FF00);
		my_mlx_pixel_put(img, 0, i, 0x0000FF00);
		my_mlx_pixel_put(img, w, i, 0x0000FF00);
	}
}

// Define your `my_mlx_pixel_put` function here

void draw_circle(t_data *img, int radius, int centerX, int centerY, int color, void *mlx, void *mlx_win) {
    int x = radius;
    int y = 0;
    int radiusError = 1 - x;

    while (x >= y) {
        // Plot points of the circle using symmetry
        my_mlx_pixel_put(img, centerX + x, centerY + y, color);
        my_mlx_pixel_put(img, centerX - x, centerY + y, color);
        my_mlx_pixel_put(img, centerX + x, centerY - y, color);
        my_mlx_pixel_put(img, centerX - x, centerY - y, color);
        my_mlx_pixel_put(img, centerX + y, centerY + x, color);
        my_mlx_pixel_put(img, centerX - y, centerY + x, color);
        my_mlx_pixel_put(img, centerX + y, centerY - x, color);
        my_mlx_pixel_put(img, centerX - y, centerY - x, color);
		
		
		mlx_put_image_to_window(mlx, mlx_win, img->img, 150, 150);
		sleep (1);
		mlx_clear_window (mlx, mlx_win);
		
        y++;

        if (radiusError < 0) {
            radiusError += 2 * y + 1;
        } else {
            x--;
            radiusError += 2 * (y - x + 1);
        }

    }
	mlx_loop(mlx);
}

void	draw_line (int x_1, int y_1, int x_2, int y_2, t_data *img, int color)
{
	// int x = x_1;
	// int y = y_1;
	int x = x_1 < x_2 ? x_1 : x_2;
	int y = y_1 < y_2 ? y_1 : y_2;
	int	dx = x_2 - x_1;
	int dy = y_2 - y_1;
	int p = (2 * dx) - dy;
	while (x <= x_2)
	{
		my_mlx_pixel_put(img, x, y, color);
		x++;
		if (p < 0)
			p = p + (2 * dy);
		else
		{
			y++ ;
			p = p + (2 * dy) - (2 * dx);
		}
	}
}

int gd_color(int color, int step, int i)
{
    unsigned char a, r, g, b;
    a = color >> 24;
    r = color >> 16;
    g = color >> 8;
    b = color;
    // printf ("r: %d, g: %d, b: %d\n", r, g, b);
    // r = r * i / step;
    // g = g * i / step;
    // b = b * i / step;
    a = 255 - (i * 255 / step);
    // printf ("r: %d, g: %d, b: %d\n", r, g, b);
    color = a;
    color = (color << 8) + r;
    color = (color << 8) + g;
    color = (color << 8) + b;
    printf ("%X\n", color);
    return (color);
}

void draw_line_dda (int x_1, int y_1, int x_2, int y_2, t_data *img, int color)
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
		// printf ("i: %d, x: %f_%d, y: %f_%d\n", i,
		// 	x, (int)floor(x), y, (int)floor(y));
		printf ("i: %d, x: %f_%d, y: %f_%d\n", i,
			x, (int)round(x), y, (int)round(y));
		// my_mlx_pixel_put(img, y, y, color);
		my_mlx_pixel_put(img, round(x), round(y), gd_color(color, step, i + 1));
		x = x + dx;
		y = y + dy;
	}
}

int	main(void)
{
	t_data	img;
	void	*mlx;
	void	*mlx_win;
	int		w;
	int		h;

	w = 400;
	h = 400;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, w, h, "Hello world!");
	img.img = mlx_new_image(mlx, w, h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
							&img.endian);
	printf("img.addr: %d, img.bits_per_pixel: %d, img.line_length: %d, img.endian: %d\n",
		*img.addr, img.bits_per_pixel, img.line_length, img.endian);
	// write_squre (&img, 100);
	// write_circle (&img, 100);
	// draw_circle (&img, 50, 50, 50 , 0x0000FF00, mlx, mlx_win);
	// draw_line_dda (0, 0, 200, 100, &img, 0x00AAFF10);
	// draw_line_dda (0, 0, 400, 380, &img, 0x00AAFF10);
	for (int i = 0; i < 20; i++){
		draw_line_dda (0, 0 + i, 400, 380 + i, &img, 0x00AAFF10);
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}