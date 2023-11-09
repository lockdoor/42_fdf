/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_add_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 10:52:22 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/08 15:22:59 by pnamnil          ###   ########.fr       */
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

static void fdf_exit_error_fd(char *msg, int fd, t_fdf *fdf)
{
	close (fd);
	fdf_free_data (fdf);
	fdf_exit_error (msg, EXIT_FAILURE);
}

static t_bool fdf_get_data(char *data, t_fdf *fdf, size_t row, size_t col)
{
	char	**split;

	split = ft_split(data, ',');
	if (!split)
		return (FALSE);
	if (split[0])
	{
		fdf->data[row][col].adj = ft_atoi(split[0]);
		if (split[1])
		{
			fdf->data[row][col].color = ft_atoi_base(split[1]);
			
			// debug
			// ft_printf ("color: %d\n", fdf->data[row][col].color);
		}
		else
			fdf->data[row][col].color = 0;
	}
	fdf_free_split (split);
	return (TRUE);
}

static void	fdf_fill_data(char *line, t_fdf *fdf, size_t row, int fd)
{
	char	**split;
	size_t	col;

	split = ft_split(line, 32);
	free (line);
	if (!split)
		fdf_exit_error_fd (MALLOC_ERROR, fd, fdf);
	col = 0;
	while (col < fdf->col)
	{
		if (split[col] == NULL)
			fdf_exit_error_fd (WRONG_LINE, fd, fdf);
		if (!fdf_get_data (split[col], fdf, row, col))
			fdf_exit_error_fd (MALLOC_ERROR, fd, fdf);
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
	while (++i < (int)fdf->row)
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
	while (++i < (int)fdf->row)
	{
		fdf->data[i] = malloc (sizeof(t_fdata) * fdf->col);
		if (!fdf->data[i])
		{
			fdf_free_data (fdf);
			fdf_exit_error (MALLOC_ERROR, EXIT_FAILURE);
		}
	}
	fdf_read_data(fdf);
}
