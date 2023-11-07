/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_read_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:50:12 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/07 11:44:32 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_count_row(t_fdf *fdf, int fd)
{
	char	*line;

	fdf->row = 1;
	while (TRUE)
	{
		line = get_next_line (fd);
		if (line == NULL)
			break ;
		fdf->row += 1;
		free (line);
	}
	close (fd);
}

static void	fdf_count_col(t_fdf *fdf)
{
	int		fd;
	char	**split;
	char	*line;

	fd = open (fdf->filename, O_RDONLY);
	if (fd == -1)
		fdf_exit_error (INVALID_FILE, EXIT_FAILURE);
	line = get_next_line(fd);
	if (!line)
	{
		close (fd);
		fdf_exit_error (NO_DATA, EXIT_FAILURE);
	}
	split = ft_split(line, 32);
	free (line);
	if (!split)
	{
		close (fd);
		fdf_exit_error (MALLOC_ERROR, EXIT_FAILURE);
	}
	fdf->col = 0;
	while (split[fdf->col])
		fdf->col += 1;
	fdf_free_split (split);
	fdf_count_row (fdf, fd);
}

void	fdf_read_file(t_fdf *fdf)
{
	fdf_count_col (fdf);
	fdf_add_data (fdf);
}
