#ifndef	FDF_H
# define FDF_H

# include <math.h>

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include "mlx.h"

typedef struct
{
	int	width;
	int height;
	int	zoom;

	int	**z_matrix;

	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int		bpp;
	int		line_length;
	int		endian;
	char	*addr;
}		t_fdf;


void	readfile(char *filename, t_fdf *data);

void	bresenham(double x, double y, double x1, double y1, t_fdf *data);
void	draw(t_fdf *data);

#endif