/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:22:31 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/04 10:31:44 by pnamnil          ###   ########.fr       */
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

