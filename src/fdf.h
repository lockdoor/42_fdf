/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:10:16 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/15 08:41:27 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include <math.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

# define WRONG_LINE "Found wrong line length. Exiting."
# define MALLOC_ERROR "malloc error."
# define NO_DATA "No data found."
# define INVALID_ARG "Invalid argument."
# define INVALID_FILE "Invalid file."

# define ON_KEYDOWN 2
# define ON_KEYUP 3
# define ON_MOUSEDOWN 4
# define ON_MOUSEUP 5
# define ON_EXPOSE 12
# define ON_DESTROY 17
# define KEY_ESC 53
# define KEY_I 34
# define KEY_P 35
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_1 18
# define KEY_2 19
# define KEY_PLUS 24
# define KEY_MINUS 27
# define KEY_0 29
# define KEY_9 25

typedef struct s_fdata
{
	int	adj;
	int	color;
}	t_fdata;

typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	t_fdata	**data;
	char	*pname;
	char	*filename;
	size_t	col;
	size_t	row;
	size_t	zoom;
	size_t	menu_x;
	int		offset_x;
	int		offset_y;
	float	angle;
	int		adj;
	size_t	width;
	size_t	height;
	t_bool	isometric;
}	t_fdf;

typedef struct s_fdf_line
{
	float	x_1;
	float	y_1;
	float	x_2;
	float	y_2;
	float	dx;
	float	dy;
	size_t	step;
	int		z_1;
	int		z_2;
	int		c_1;
	int		c_2;
}	t_fdf_line;

// debug.c
void	print_data_debug(t_fdf *fdf);
void	print_split(char **split);

// fdf_utils.c
void	fdf_exit_error(char *strerr, int error_code);
void	fdf_exit_error_fd(char *msg, int fd, t_fdf *fdf);
int		ft_atoi_base(char *s);
int		fdf_percent(int n, int p);

// fdf_free.c
void	fdf_free_split(void *data);
void	fdf_free_data(t_fdf *fdf);

// fdf_read_file.c
void	fdf_read_file(t_fdf *fdf);

// fdf_add_data.c
void	fdf_add_data(t_fdf *fdf);

// fdf_draw_image.c
void	fdf_draw_image(t_fdf *fdf);

// fdf_bresenham.c
void	fdf_bresenham(t_fdf_line *line, t_fdf *fdf);

// fdf_gradient.c
int		fdf_gradient(t_fdf_line *line, int i);

// fdf_key_hook.c
int		key_hook(int keycode, void *param);
int		on_destroy(void *param);

// fdf_control.c
void	fdf_transform(int keycode, t_fdf *fdf);
void	fdf_projection_mode(int keycode, t_fdf *fdf);
void	fdf_modify_height(int keycode, t_fdf *fdf);
void	fdf_change_zoom(int keycode, t_fdf *fdf);
void	fdf_change_angle(int keycode, t_fdf *fdf);

#endif