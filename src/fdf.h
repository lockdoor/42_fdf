/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:10:16 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/06 12:38:45 by pnamnil          ###   ########.fr       */
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

typedef struct s_fdata
{
	int	adj;
	int	color;
}	t_fdata;


typedef struct s_fdf
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
	struct s_fdata		*data;
	char		*pname;
	char		*filename;
	size_t		col;
	size_t		row;
	size_t		zoom;
	float		angle;
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
}	t_fdf_line;

enum 
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

// debug.c
void	print_data_debug(t_fdf *fdf);
void	print_split(char **split);

// fdf_utils.c
void	fdf_exit_error(char *strerr, int error_code);

// fdf_free.c
void	fdf_free_split(void *data);
// void	fdf_free_data(t_fdf *fdf);

// fdf_read_file.c
void	fdf_read_file(t_fdf *fdf);

// fdf_add_data.c
void fdf_add_data(t_fdf *fdf);

// 
void fdf_draw_image(t_fdf *fdf);

// fdf_key_hook.c
int	key_hook(int keycode, void *param);
int on_destroy(void *param);

#endif