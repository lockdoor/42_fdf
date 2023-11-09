/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 10:21:57 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/09 10:13:34 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int on_destroy(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *) param;
		fdf_free_data (fdf);
	exit (0);
}

void	transform(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_UP)
		fdf->offset_y -= 10;
	if (keycode == KEY_DOWN)
		fdf->offset_y += 10;
	if (keycode == KEY_LEFT)
		fdf->offset_x -= 10;
	if (keycode == KEY_RIGHT)
		fdf->offset_x += 10;
	fdf_draw_image (fdf);
}

void	projection_mode(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_I)
		fdf->isometric = TRUE;
	if (keycode == KEY_P)
		fdf->isometric = FALSE;
	fdf_draw_image (fdf);
}

void	modify_height(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_1)
		fdf->adj -= 1;
	if (keycode == KEY_2)
		fdf->adj += 1;
	fdf_draw_image (fdf);
}

void	zoom(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_PLUS)
		fdf->zoom += 1;
	if (keycode == KEY_MINUS && fdf->zoom > 1)
		fdf->zoom -= 1;
	fdf_draw_image (fdf);
}

void	change_angle(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_0)
		fdf->angle += 0.1;
	if (keycode == KEY_9)
		fdf->angle -= 0.1;
	fdf_draw_image (fdf);
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
		projection_mode (keycode, fdf);
	if (keycode >= KEY_LEFT && keycode <= KEY_UP)
		transform (keycode, fdf);
	if (keycode == KEY_1 || keycode == KEY_2)
		modify_height (keycode, fdf);
	if (keycode == KEY_PLUS || keycode == KEY_MINUS)
		zoom (keycode, fdf);
	if (keycode == KEY_0 || keycode == KEY_9)
		change_angle (keycode, fdf);
	ft_printf ("Hello from key_hook!: %d\n", keycode);
	return (0);
}
