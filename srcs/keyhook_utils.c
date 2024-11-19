/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:18:17 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/19 11:07:17 by aapadill         ###   ########.fr       */
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
		gc_perror("Invalid axis", 0);
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
		gc_perror("Invalid transformation mode", 0);
	return (ptr);
}

/*
 * Copy the values from map src to map dst
 * improv: free both maps before perror
 */
void	copy_map(t_map *dst, t_hook_params *h_p)
{
	int	i;
	int	j;

	i = -1;
	dst->x = h_p->map->x;
	dst->y = h_p->map->y;
	dst->cells = gc_alloc(sizeof(t_cell *) * h_p->map->y);
	if (!dst->cells)
	{
		mlx_terminate(h_p->mlx);
		gc_perror("Malloc error (copy_map)", 1);
	}
	while (++i < h_p->map->y)
	{
		dst->cells[i] = gc_alloc(sizeof(t_cell) * h_p->map->x);
		if (!dst->cells[i])
		{
			mlx_terminate(h_p->mlx);
			gc_perror("Malloc error (copy_map)", 1);
		}
		j = -1;
		while (++j < h_p->map->x)
			dst->cells[i][j] = h_p->map->cells[i][j];
	}
}
