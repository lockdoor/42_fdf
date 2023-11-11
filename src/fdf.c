/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:14:40 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/11 10:18:57 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_control(t_fdf *fdf)
{
	mlx_string_put (fdf->mlx, fdf->win, 10, 30, 0xFFFFFFF, "Control");
	mlx_string_put (fdf->mlx, fdf->win, 10, 60, 0xFFFFFFF, "3D: I");
	mlx_string_put (fdf->mlx, fdf->win, 10, 90, 0xFFFFFFF, "2D: P");
	mlx_string_put (fdf->mlx, fdf->win, 10, 120, 0xFFFFFFF, "Transform: Arrow");
	mlx_string_put (fdf->mlx, fdf->win, 10, 150, 0xFFFFFFF, "Height: [1], [2]");
	mlx_string_put (fdf->mlx, fdf->win, 10, 180, 0xFFFFFFF, "Zoom: [+], [-]");
	mlx_string_put (fdf->mlx, fdf->win, 10, 210, 0xFFFFFFF, "Angle: [9], [0]");
}

static void	init_fdf(t_fdf *fdf, char **argv)
{
	ft_bzero (fdf, sizeof(fdf));
	fdf->pname = argv[0];
	fdf->filename = argv[1];
	fdf->adj = 1;
	fdf->isometric = FALSE;
	fdf->angle = 1;
	fdf->zoom = 1;
	fdf->offset_x = 250;
	fdf->offset_y = 170;
	fdf->menu_x = 200;
	fdf->width = 1200;
	fdf->height = 800;
}

static void	find_zoom(t_fdf *fdf)
{
	while ((fdf->col * fdf->zoom < fdf->width)
		&& (fdf->row * fdf->zoom < fdf->height))
	{
		fdf->zoom += 1;
	}
	if (fdf->zoom > 1)
		fdf->zoom -= 1;
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		fdf_exit_error (INVALID_ARG, EXIT_FAILURE);
	init_fdf (&fdf, argv);
	fdf_read_file (&fdf);
	find_zoom (&fdf);
	fdf.mlx = mlx_init ();
	fdf.win = mlx_new_window (fdf.mlx, fdf.width + fdf.menu_x, \
		fdf.height, fdf.filename);
	fdf.img = mlx_new_image (fdf.mlx, fdf.width, fdf.height);
	fdf.addr = mlx_get_data_addr (fdf.img, &fdf.bpp, \
		&fdf.line_length, &fdf.endian);
	mlx_hook (fdf.win, ON_KEYUP, 0, key_hook, &fdf);
	mlx_hook (fdf.win, ON_DESTROY, 0, on_destroy, &fdf);
	fdf_control (&fdf);
	fdf_draw_image (&fdf);
	mlx_loop (fdf.mlx);
	return (0);
}
