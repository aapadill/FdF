/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:18:17 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/07 19:42:21 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 * Returns the address of the parameter to be modified, assumes:
 * 0) transformations are only rotation, translation and scaling
 * 1) x, y, z are defined in order in the t_hook_params struct 
 * 2) the axis are either 'x', 'y' or 'z' (only).
 * improve: you need to free everything before both ft_perror calls
 */
float	*parameter_finder(t_hook_params	*h_p, t_axis axis)
{
	float	*ptr;

	ptr = NULL;
	if (axis < x_axis || axis > no_axis)
		ft_perror("Invalid axis", 0);
	if (h_p->transf == s_mode)
	{
		h_p->step = s_constant;
		ptr = &h_p->sx + axis;
	}
	if (h_p->transf == r_mode)
	{
		h_p->step = r_degrees;
		ptr = &h_p->rx + axis;
		if (*ptr >= 360)
			*ptr -= 360;
	}
	if (h_p->transf == t_mode)
	{
		h_p->step = t_pixels;
		ptr = &h_p->tx + axis;
	}
	if (!ptr)
		ft_perror("Invalid transformation mode", 0);
	return (ptr);
}

/*
 * Copy the values from map src to map dst
 * improv: free both maps before perror
 */
int	copy_map(t_map *dst, t_map *src)
{
	int	i;
	int	j;

	i = -1;
	dst->x = src->x;
	dst->y = src->y;
	dst->cells = malloc(sizeof(t_cell *) * src->y);
	if (!dst->cells)
	{
		ft_putendl_fd("Malloc error (copy_map)", 2);
		return (-1);
	}
	while (++i < src->y)
	{
		dst->cells[i] = malloc(sizeof(t_cell) * src->x);
		if (!dst->cells[i])
		{
			ft_free(i, (void **)dst->cells);
			ft_putendl_fd("Malloc error (copy_map)", 2);
			return (-1);
		}
		j = -1;
		while (++j < src->x)
			dst->cells[i][j] = src->cells[i][j];
	}
	return (1);
}
