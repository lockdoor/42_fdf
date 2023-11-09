/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:22:31 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/08 12:47:58 by pnamnil          ###   ########.fr       */
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

void fdf_free_data (t_fdf *fdf)
{
	int		i;
	t_fdata **data;

	data = fdf->data;
	if (!data)
		return ;
	i = 0;
	while (data[i] && i < (int)fdf->row)
	{
		free (data[i]);
		data[i] = NULL;
		i++ ;
	}
	free (data);
	fdf->data = NULL;
}
