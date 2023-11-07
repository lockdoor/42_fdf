/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:14:40 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/07 11:18:52 by pnamnil          ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	/* check number of argument */
	if (argc != 2)
		fdf_exit_error (INVALID_ARG, EXIT_FAILURE);

	/* read file */
	ft_bzero (&fdf, sizeof(fdf));
	fdf.pname = argv[0];
	fdf.filename = argv[1];
	fdf_read_file (&fdf);

	/* prepair window and image */
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, 800, 800, fdf.filename);
	fdf.img = mlx_new_image(fdf.mlx, 800, 800);
	fdf.addr = mlx_get_data_addr(fdf.img, &fdf.bpp, &fdf.line_length, &fdf.endian);

	/* draw image */
	fdf.zoom = 30;
	fdf.shift = 170;
	fdf_draw_image (&fdf);
	mlx_put_image_to_window(fdf.mlx, fdf.win, fdf.img, 0, 0);
	

	/* hook */
	mlx_hook (fdf.win, ON_KEYUP, 0, key_hook, &fdf);
	// mlx_hook (fdf.win, 5, 0, mouse_event, &fdf);
	mlx_hook (fdf.win, ON_DESTROY, 0, on_destroy, &fdf);

	
	mlx_loop(fdf.mlx);
	
	return (0);
}