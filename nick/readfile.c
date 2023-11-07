#include "fdf.h"
#include "fcntl.h"

int	get_height(char *filename)
{
	char	*line;
	int	height;
	int fd = open (filename, O_RDONLY);

	height = 0;
	while ((line = get_next_line(fd)))
	{
		free (line);
		height++ ;
	}
	close (fd);
	return (height);
}

int	count_word(char *line)
{
	int i;

	i = 0;
	while (*line)
	{
		while (*line && *line == 32)
		{
			line ++;
		}
		if (*line)
		{
			i++ ;
		}
		while (*line && *line != 32)
		{
			line ++;
		}
	}
	return (i);
}

int	get_width(char *filename)
{
	int		fd = open (filename, O_RDONLY);
	char	*line;
	int		width;

	line = get_next_line (fd);
	width = count_word (line);
	free (line);
	close (fd);
	return (width);
}

void	fdf_free_split(void *data)
{
	char	**split;

	split = (char **) data;
	if (!split)
		return ;
	while (*split)
	{
		free (*split);
		*split = NULL;
		split++ ;
	}
	free (data);
	data = NULL;
}

void	fill_matrix(t_fdf *data, char *line, int x)
{
	char	**split;
	int		i;

	split = ft_split (line, 32);
	i = -1;
	while (++i < data->width)
	{
		data->z_matrix[x][i] = ft_atoi(split[i]);
	}
	fdf_free_split (split);
}

void	print_debug (t_fdf *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			ft_printf ("%3d", data->z_matrix[i][j]);
			j++ ;
		}
		ft_printf ("\n");
		i++ ;
	}
}

void	readfile(char *filename, t_fdf *data)
{
	char	*line;
	int	fd;
	int	i;

	data->height = get_height (filename);
	data->width = get_width (filename);
	// ft_printf ("hieght: %d, width: %d\n", data->height, data->width);
	data->z_matrix = malloc ((data->height) * sizeof(int *));
	
	fd = open (filename, O_RDONLY);
	i = -1;
	while (++i < data->height)
	{
		data->z_matrix[i] = malloc ((data->width) * sizeof(int));
		line = get_next_line (fd);
		fill_matrix (data, line, i);
		free (line);
	}

	close (fd); 
	
	// print_debug (data);
}