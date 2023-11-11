/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 10:21:57 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/11 10:16:24 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	on_destroy(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *) param;
	fdf_free_data (fdf);
	exit (0);
}

int	key_hook(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *) param;
	if (keycode == KEY_ESC)
	{
		mlx_destroy_image (fdf->mlx, fdf->img);
		mlx_destroy_window (fdf->mlx, fdf->win);
		on_destroy (fdf);
	}
	if (keycode == KEY_I || keycode == KEY_P)
		fdf_projection_mode (keycode, fdf);
	if (keycode >= KEY_LEFT && keycode <= KEY_UP)
		fdf_transform (keycode, fdf);
	if (keycode == KEY_1 || keycode == KEY_2)
		fdf_modify_height (keycode, fdf);
	if (keycode == KEY_PLUS || keycode == KEY_MINUS)
		fdf_zoom (keycode, fdf);
	if (keycode == KEY_0 || keycode == KEY_9)
		fdf_change_angle (keycode, fdf);
	return (0);
}

// ft_printf ("Hello from key_hook!: %d\n", keycode);
