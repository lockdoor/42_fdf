/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_gradient.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:54:25 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/11 09:50:36 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_init_color(int c, int alt, u_int8_t *u)
{
	if (c)
	{
		u[0] = c >> 24;
		u[1] = c >> 16;
		u[2] = c >> 8;
		u[3] = c;
	}
	else if (alt)
	{
		u[0] = 0;
		u[1] = 0xFF;
		u[2] = 0xFF;
		u[3] = 0;
	}
	else
	{
		u[0] = 0;
		u[1] = 0xFF;
		u[2] = 0xFF;
		u[3] = 0xFF;
	}
}

int	fdf_gradient(t_fdf_line *line, int i)
{
	u_int8_t	start[4];
	u_int8_t	end[4];
	u_int8_t	res[3];
	int			result;
	float		step[3];

	fdf_init_color(line->c_1, line->z_1, start);
	fdf_init_color(line->c_2, line->z_2, end);
	step[0] = (float)(end[1] - start[1]) / line->step;
	step[1] = (float)(end[2] - start[2]) / line->step;
	step[2] = (float)(end[3] - start[3]) / line->step;
	res[0] = start[1] + i * step[0];
	res[1] = start[2] + i * step[1];
	res[2] = start[3] + i * step[2];
	result = res[0] << 16 | res[1] << 8 | res[2];
	return (result);
}

// int	gradient(t_fdf_line *line, int i)
// {
// 	int start;
// 	int end;
// 	if (line->c_1)
// 		start = line->c_1;
// 	else if (line->z_1)
// 		start = 0xFFFF00;
// 	else
// 		start = 0xFFFFFF;
// 	if (line->c_2)
// 		end = line->c_2;
// 	else if (line->z_2)
// 		end = 0xFFFF00;
// 	else
// 		end = 0xFFFFFF;
// 	u_int8_t sr = start >> 16;
// 	u_int8_t sg = start >> 8;
// 	u_int8_t sb = start;
// 	u_int8_t er = end >> 16;
// 	u_int8_t eg = end >> 8;
// 	u_int8_t eb = end;
// 	float	st_r = (float)(er - sr) / line->step;
// 	float	st_g = (float)(eg - sg) / line->step;
// 	float	st_b = (float)(eb - sb) / line->step;
// 	u_int8_t rr = (sr + i * st_r);
// 	u_int8_t rg = (sg + i * st_g);
// 	u_int8_t rb = (sb + i * st_b);
// 	return (rr << 16 | rg << 8 | rb);
// }
