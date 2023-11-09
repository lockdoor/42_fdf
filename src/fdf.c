/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:14:40 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/08 16:11:22 by pnamnil          ###   ########.fr       */
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
static void	init_fdf(t_fdf *fdf, char **argv)
{
	ft_bzero (fdf, sizeof(fdf));
	fdf->pname = argv[0];
	fdf->filename = argv[1];
	fdf->adj = 10;
	fdf->isometric = TRUE;
	fdf->angle = 0.8;
	fdf->zoom = 20;
	fdf->offset_x = 170;
	fdf->offset_y = 170;
	fdf->menu_x = 200;
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

	/* prepair window and image */
	fdf.width = ((fdf.col - 1) * fdf.zoom) + (fdf.offset_x * 2);
	fdf.height = ((fdf.row - 1) * fdf.zoom) + (fdf.offset_y * 2);
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, fdf.width + fdf.menu_x, fdf.height, fdf.filename);
	fdf.img = mlx_new_image(fdf.mlx, fdf.width, fdf.height);
	fdf.addr = mlx_get_data_addr(fdf.img, &fdf.bpp, &fdf.line_length, &fdf.endian);

	/* hook */
	mlx_hook (fdf.win, ON_KEYUP, 0, key_hook, &fdf);
	// mlx_hook (fdf.win, 5, 0, mouse_event, &fdf);
	mlx_hook (fdf.win, ON_DESTROY, 0, on_destroy, &fdf);

	/* draw image */
	fdf_draw_image (&fdf);

	mlx_loop(fdf.mlx);
	
	return (0);
}