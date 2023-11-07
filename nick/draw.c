#include "fdf.h"

static void	my_mlx_pixel_put(t_fdf *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void	isometric(double *x, double *y, int z, double angle)
{
	*x = (*x - *y) * cos(angle);
	*y = ((*x + *y) * sin(angle)) - z;
}

void	bresenham(double x, double y, double x1, double y1, t_fdf *data)
{
	double	x_step;
	double	y_step;
	double	step;

	/* color */
	int z = data->z_matrix[(int)y][(int)x];
	int z1 = data->z_matrix[(int)y1][(int)x1];
	int color = z ? 0xFF0000 : 0xFFFFFF;

	/* zoom */
	x *= data->zoom;
	y *= data->zoom;
	x1 *= data->zoom;
	y1 *= data->zoom;

	/* 3D */
	isometric (&x, &y, z, 1);
	isometric (&x1, &y1, z1, 1);

	/* shift */
	int shift = 170;
	x += shift;
	y += shift;
	x1 += shift;
	y1 += shift;



	x_step = x1 - x;
	y_step = y1 - y;

	step = fmax(fabs(x_step), fabs(y_step));
	x_step /= step;
	y_step /= step;

	while ((int)(x - x1) || (int)(y - y1))
	{
		// mlx_pixel_put (data->mlx_ptr, data->win_ptr, (int)x, (int)y, color);
		my_mlx_pixel_put (data, (int)round(x), (int)round(y), color);
		x += x_step;
		y += y_step;
	}
}

void	draw(t_fdf *data)
{
	int	x;
	int y;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (x < data->width - 1)
				bresenham(x, y, x + 1, y, data);
			if (y < data->height - 1)
				bresenham(x, y, x, y + 1, data);
			x++ ;
		}
		y++ ;
	}
}