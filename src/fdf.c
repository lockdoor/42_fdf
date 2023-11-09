/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:14:40 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/09 11:17:11 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// int	mouse_event(int button, int x, int y, void *param)
// {
// 	t_fdf	*fdf;

// 	(void)	button;
// 	fdf = (t_fdf *) param;
// 	ft_printf ("x: %d, y: %d\n", x, y);
// 	ft_printf ("x: ", fdf->win);
// 	return (0);
// }

// int	expose_event(void *param)
// {
// 	(void) param;
// 	ft_printf ("expose event\n");
// 	return (0);
// }

void	menu(t_fdf *fdf)
{
	/* menu */
	mlx_string_put (fdf->mlx, fdf->win, 10, 10, 0xFFFFFFF, "Menu");
	mlx_string_put (fdf->mlx, fdf->win, 10, 30, 0xFFFFFFF, "Control");
	mlx_string_put (fdf->mlx, fdf->win, 10, 70, 0xFFFFFFF, "3D: I");
	mlx_string_put (fdf->mlx, fdf->win, 10, 100, 0xFFFFFFF, "2D: P");
	mlx_string_put (fdf->mlx, fdf->win, 10, 130, 0xFFFFFFF, "Transform: Arrow");
	mlx_string_put (fdf->mlx, fdf->win, 10, 170, 0xFFFFFFF, "Height: [1], [2]");
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

static void find_zoom(t_fdf *fdf)
{
	while ((fdf->col * fdf->zoom < fdf->width)
		&& (fdf->row * fdf->zoom < fdf->height))
	{
		fdf->zoom += 1;
	}
	if (fdf->zoom > 1)
		fdf->zoom -= 1;
}

/*
	Do next
	find proper size of window
	zoom in - out
	rotate x y z
*/

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	/* check number of argument */
	if (argc != 2)
		fdf_exit_error (INVALID_ARG, EXIT_FAILURE);

	init_fdf (&fdf, argv);
	
	/* read file */
	fdf_read_file (&fdf);

	/* find proper size of window */
	find_zoom (&fdf);

	/* prepair window and image */
	// fdf.width = ((fdf.col - 1) * fdf.zoom) + (fdf.offset_x * 2);
	// fdf.height = ((fdf.row - 1) * fdf.zoom) + (fdf.offset_y * 2);
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, fdf.width + fdf.menu_x, fdf.height, fdf.filename);
	fdf.img = mlx_new_image(fdf.mlx, fdf.width, fdf.height);
	fdf.addr = mlx_get_data_addr(fdf.img, &fdf.bpp, &fdf.line_length, &fdf.endian);

	/* hook */
	mlx_hook (fdf.win, ON_KEYUP, 0, key_hook, &fdf);
	// mlx_hook (fdf.win, 5, 0, mouse_event, &fdf);
	mlx_hook (fdf.win, ON_DESTROY, 0, on_destroy, &fdf);

	menu(&fdf);
	/* draw image */
	fdf_draw_image (&fdf);

	mlx_loop(fdf.mlx);
	
	return (0);
}