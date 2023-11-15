/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 10:10:26 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/15 08:34:11 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_transform(int keycode, t_fdf *fdf)
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

void	fdf_projection_mode(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_I)
	{
		fdf->offset_x = fdf_percent(fdf->width, 45);
		fdf->offset_y = fdf_percent(fdf->height, 15);
		fdf->zoom = fdf_percent(fdf->zoom, 25);
		fdf->isometric = TRUE;
	}
	if (keycode == KEY_P)
		fdf->isometric = FALSE;
	fdf_draw_image (fdf);
}

void	fdf_modify_height(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_1)
		fdf->adj -= 1;
	if (keycode == KEY_2)
		fdf->adj += 1;
	fdf_draw_image (fdf);
}

void	fdf_change_zoom(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_PLUS)
		fdf->zoom += 1;
	if (keycode == KEY_MINUS && fdf->zoom > 1)
		fdf->zoom -= 1;
	fdf_draw_image (fdf);
}

void	fdf_change_angle(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_0)
		fdf->angle += 0.1;
	if (keycode == KEY_9)
		fdf->angle -= 0.1;
	fdf_draw_image (fdf);
}
