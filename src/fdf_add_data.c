/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_add_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 10:52:22 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/07 11:47:26 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_rm_newline(char *line)
{
	char	*nl;

	nl = ft_strrchr(line, '\n');
	if (nl)
		*nl = 0;
}

static void	fdf_fill_data(char *line, t_fdf *fdf, size_t row, int fd)
{
	char	**split;
	size_t	col;

	split = ft_split(line, 32);
	free (line);
	if (!split)
	{
		close (fd);
		fdf_free_data (fdf);
		fdf_exit_error (MALLOC_ERROR, EXIT_FAILURE);
	}
	col = 0;
	while (col < fdf->col)
	{
		if (split[col] == NULL)
		{
			close (fd);
			free (fdf);
			fdf_exit_error (WRONG_LINE, EXIT_FAILURE);
		}
		fdf->data[row][col].adj = ft_atoi (split[col]);
		fdf->data[row][col].color = 0;
		col++ ;
	}
	fdf_free_split (split);
}

/* open file and get each line */
static void	fdf_read_data(t_fdf *fdf)
{
	int		fd;
	char	*line;
	int		i;

	fd = open (fdf->filename, O_RDONLY);
	if (fd == -1)
	{
		fdf_free_data (fdf);
		fdf_exit_error (INVALID_FILE, EXIT_FAILURE);
	}
	i = -1;
	while (++i < fdf->row)
	{
		line = get_next_line(fd);
		if (!line)
		{
			close (fd);
			fdf_free_data (fdf);
			fdf_exit_error (fdf->filename, EXIT_FAILURE);
		}
		fdf_rm_newline (line);
		fdf_fill_data (line, fdf, i, fd);
	}
	close (fd);
}

/* malloc stage */
void	fdf_add_data(t_fdf *fdf)
{
	int		i;

	fdf->data = ft_calloc (fdf->row, sizeof(t_fdata *));
	if (!fdf->data)
		fdf_exit_error (MALLOC_ERROR, EXIT_FAILURE);
	i = -1;
	while (++i < fdf->row)
	{
		fdf->data[i] = malloc (sizeof(t_fdata) * fdf->col);
		if (!fdf->data[i])
		{
			fdf_free_data (fdf->data);
			fdf_exit_error (MALLOC_ERROR, EXIT_FAILURE);
		}
	}
	fdf_read_data(fdf);
}
