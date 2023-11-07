#include "fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	*data;

	(void) argc;
	data = (t_fdf *) malloc (sizeof(t_fdf));
	readfile(argv[1], data);

	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, 800, 800, argv[1]);
	// data->img_ptr = mlx_new_image(data->mlx_ptr, 500, 500);
	// data->addr = mlx_get_data_addr(data->img_ptr, &data->bpp, &data->line_length, &data->endian);

	// for (int i = 0; i < 100; i += 20)
	// {
	// 	bresenham (10, 10 + i, 100, 10 + i, data);
	// }
	// bresenham (10, 10, 100, 100, data);
	// bresenham (20, 20, 100, 100, data);
	data->zoom = 20;
	draw(data);
	// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);


	// mlx_key_hook (data->win_ptr, 3);
	mlx_loop(data->mlx_ptr);
	
	return (0);
}