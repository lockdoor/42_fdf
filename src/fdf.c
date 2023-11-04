/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:14:40 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/03 17:03:01 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	// void	*mlx;
	t_fdf	fdf;

	// check number of argument
	if (argc != 2)
	{
		errno = EINVAL;
		fdf_exit_error (argv[0], EXIT_FAILURE);
	}

	// read file
	ft_bzero (&fdf, sizeof(fdf));
	fdf_read_file (&fdf, argv);
	// mlx = mlx_init();
	// mlx_win = mlx_new_window(mlx, 400, 400, "Hello world!");
	// mlx_new_window(mlx, 400, 400, "Hello world!");
	// mlx_loop(mlx);

	
	return (0);
}