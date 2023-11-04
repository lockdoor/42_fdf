/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:10:16 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/03 16:32:35 by pnamnil          ###   ########.fr       */
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

typedef struct s_fdf
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		**data;
	size_t	data_col;
	size_t	data_row;
}	t_fdf;

// debug.c
void	print_data_debug(t_fdf *fdf);
void	print_split(char **split);

// fdf_utils.c
void	fdf_exit_error(char *strerr, int error_code);

// fdf_free.c
void	fdf_free_split(void *data);
void	fdf_free_data(t_fdf *fdf);

// fdf_read_file.c
void	fdf_read_file (t_fdf *fdf, char **argv);

#endif