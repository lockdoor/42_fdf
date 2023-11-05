/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_add_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 10:52:22 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/05 13:34:22 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void fdf_add_col(char *line, t_fdf *fdf, size_t row, int fd)
{
	char	**split;
	size_t	col;

	split = ft_split(line, 32);
	free (line);
	if (!split)
	{
		close (fd);
		free (fdf->data);
		fdf_exit_error (MALLOC_ERROR, EXIT_FAILURE);
	}
	col = 0;
	while (col < fdf->col)
	{
		if (split[col] == NULL)
		{
			close (fd);
			free (fdf->data);
			fdf_exit_error (WRONG_LINE, EXIT_FAILURE);
		}
		fdf->data[(row * fdf->col) + col].adj = ft_atoi (split[col]);
		col++ ;
	}
	fdf_free_split (split);	
}

static void fdf_rm_newline(char *line)
{
	char	*nl;

	nl = ft_strrchr(line, '\n');
	if (nl)
		*nl = 0;
}

void fdf_add_data(t_fdf *fdf)
{
	int		fd;
	char	*line;
	size_t	row;

	fd = open (fdf->filename, O_RDONLY);
	
	if (fd == -1)
	{
		free (fdf->data);
		fdf_exit_error (INVALID_FILE, EXIT_FAILURE);
	}
	row = 0;
	while (row < fdf->row)
	{
		line = get_next_line(fd);
		if (!line)
		{
			close (fd);
			free (fdf->data);
			fdf_exit_error (fdf->filename, EXIT_FAILURE);
		}
		fdf_rm_newline (line);
		fdf_add_col (line, fdf, row, fd);
		row++ ;
	}
	close (fd);
}