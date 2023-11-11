/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:11:31 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/11 10:19:18 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_exit_error(char *strerr, int error_code)
{
	ft_putendl_fd (strerr, 2);
	exit (error_code);
}

void	fdf_exit_error_fd(char *msg, int fd, t_fdf *fdf)
{
	close (fd);
	fdf_free_data (fdf);
	fdf_exit_error (msg, EXIT_FAILURE);
}

static int	find_index(char *base, char c)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == ft_toupper(c))
			return (i);
		i++ ;
	}
	return (-1);
}

int	ft_atoi_base(char *s)
{
	int		n;
	char	*base;
	int		idx;

	n = 0;
	base = "0123456789ABCDEF";
	if (!s)
		return (n);
	if (ft_strlen (s) > 10)
		return (n);
	if (ft_strncmp (s, "0x", 2))
		return (n);
	s += 2 ;
	while (*s)
	{
		idx = find_index (base, *s);
		if (idx == -1)
			break ;
		n = (n * 16) + idx;
		s++ ;
	}
	return (n);
}
