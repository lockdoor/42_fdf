/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:22:31 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/03 16:16:59 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	fdf_free_data(t_fdf *fdf)
{
	size_t	i;
	size_t	size;

	if (!fdf->data)
		return ;
	i = 0;
	size = fdf->data_col * fdf->data_row;
	while (i < size)
	{
		free (fdf->data[i]);
		fdf->data[i] = NULL;
		i++ ;
	}
	free (fdf->data);
	fdf->data = NULL;
}
