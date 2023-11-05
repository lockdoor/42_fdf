#include "../libft/includes/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int	fd;
	char	*line;

	fd = open ("../empty_file", O_RDONLY);
	printf ("fd: %d\n", fd);
	while ((line = get_next_line(fd)))
	{
		printf ("%s\n", line);
		free (line);
	}
	close (fd);
	fd = open ("../empty_file", O_RDONLY);
	printf ("fd: %d\n", fd);
	while ((line = get_next_line(fd)))
	{
		printf ("%s\n", line);
		free (line);
	}
	close (fd);
	return (0);
}
