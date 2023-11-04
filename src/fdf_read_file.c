/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_read_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:50:12 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/04 07:31:20 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
static void	fdf_count_col_row(t_fdf *fdf, char **argv, int fd)
{
	char	**split;
	char	*line;

	line = get_next_line(fd);
	if (line)
	{
		fdf->data_row = 1;
		split = ft_split(line, 32);
		if (!split)
		{
			free (line);
			close (fd);
			fdf_exit_error (argv[0], fdf, EXIT_FAILURE);
		}
		fdf->data_col = 0;
		while (split[fdf->data_col])
			fdf->data_col += 1;
		fdf_free_split (split);
		free (line);
	}
	while (TRUE)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		fdf->data_row += 1;	
		free (line);
	}
}
*/

static void	fdf_count_row(t_fdf *fdf, int fd)
{
	char	*line;

	if (!fdf->data_col)
	{
		close (fd);
		fdf_exit_error ("No data found.", EXIT_FAILURE);
	}
	fdf->data_row = 1;
	while (TRUE)
	{
		line = get_next_line (fd);
		if (line == NULL)
			break ;	
		fdf->data_row += 1;
		free (line);
	}
	close (fd);
	if (!fdf->data_row)
		fdf_exit_error ("No data found.", EXIT_FAILURE);
}

static void	fdf_count_col(t_fdf *fdf, char **argv)
{
	int		fd;
	char	**split;
	char	*line;

	fd = open (argv[1], O_RDONLY);
	if (fd == -1)
		fdf_exit_error (argv[1], EXIT_FAILURE);
	line = get_next_line(fd);
	if (!line)
	{
		close (fd);	
		fdf_exit_error ("No data found.", EXIT_FAILURE);
	}
	split = ft_split(line, 32);
	free (line);
	if (!split)
	{
		close (fd);
		fdf_exit_error (argv[0], EXIT_FAILURE);
	}
	fdf->data_col = 0;
	while (split[fdf->data_col])
		fdf->data_col += 1;
	fdf_free_split (split);
	fdf_count_row (fdf, fd);
}

// static void fdf_add_data(t_fdf *fdf, char **argv, int fd)
// {
// 	(void)	argv;
// 	char	*line;
// 	char	**split;
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	while (i < fdf->data_row)
// 	{
// 		/*protect this*/
// 		line = get_next_line(fd);
// 		/*protect this*/
// 		split = ft_split(line, 32);
// 		free (line);
// 		j = 0;
// 		while (j < fdf->data_col)
// 		{
// 			/*protect this*/
// 			fdf->data[(i * fdf->data_col) + j] = malloc (sizeof(int) * 2);
// 			fdf->data[(i * fdf->data_col) + j][0] =  ft_atoi (split[j]);
// 			j++ ;
// 		}
// 		fdf_free_split (split);
// 		i++ ;
// 	}
// }





void	fdf_read_file (t_fdf *fdf, char **argv)
{
	// int fd;

	/* count stage */
	fdf_count_col (fdf, argv);
	// fdf_count_row (fdf, argv);
	
	/* debug */
	ft_printf ("row: %d, col: %d\n", fdf->data_row, fdf->data_col);
	
	// /* malloc stage */
	// fdf->data = malloc (fdf->data_col * fdf->data_row * sizeof(int *));
	// if (!fdf->data)
	// 	fdf_exit_error (argv[0], EXIT_FAILURE);

	// /* add data stage */
	// fd = open (argv[1], O_RDONLY);
	// if (fd == -1)
	// 	fdf_exit_error (argv[1], EXIT_FAILURE);
	// fdf_add_data (fdf, argv, fd);
	// close (fd);

	// print_data_debug (fdf);
	// fdf_free_data (fdf);
}