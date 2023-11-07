/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 10:21:57 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/07 10:57:48 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int on_destroy(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *) param;
		fdf_free_data (fdf->data);
	exit (0);
}

int	key_hook(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *) param;
	if (keycode == 53)
	{
		mlx_destroy_window (fdf->mlx, fdf->win);	
		on_destroy (fdf);
	}
	ft_printf ("Hello from key_hook!: %d\n", keycode);
	return (0);
}
