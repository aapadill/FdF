/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 03:24:32 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/25 19:41:50 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	translate_map(t_map *map, float tx, float ty, float tz)
{
	int	j;
	int	i;

	compute_center(map);
	j = -1;
	while (++j < map->y)
	{
		i = -1;
		while (++i < map->x)
		{
			map->cells[j][i].x -= map->info.center_x;
			map->cells[j][i].y -= map->info.center_y;
			map->cells[j][i].z -= map->info.center_z;
			map->cells[j][i].x += tx;
			map->cells[j][i].y += ty;
			map->cells[j][i].z += tz;
			map->cells[j][i].x += map->info.center_x;
			map->cells[j][i].y += map->info.center_y;
			map->cells[j][i].z += map->info.center_z;
		}
	}
}

void	scale_map(t_map *map, float sx, float sy, float sz)
{
	int	j;
	int	i;

	compute_center(map);
	j = -1;
	while (++j < map->y)
	{
		i = -1;
		while (++i < map->x)
		{
			map->cells[j][i].x -= map->info.center_x;
			map->cells[j][i].y -= map->info.center_y;
			map->cells[j][i].x *= sx;
			map->cells[j][i].y *= sy;
			map->cells[j][i].z *= sz;
			map->cells[j][i].x += map->info.center_x;
			map->cells[j][i].y += map->info.center_y;
		}
	}
}

void	rotate_map(t_map *map, float angle_x, float angle_y, float angle_z)
{
	int	j;
	int	i;

	compute_center(map);
	j = -1;
	while (++j < map->y)
	{
		i = -1;
		while (++i < map->x)
		{
			map->cells[j][i].x -= map->info.center_x;
			map->cells[j][i].y -= map->info.center_y;
			map->cells[j][i].z -= map->info.center_z;
			rotate_x_axis(&map->cells[j][i].y, &map->cells[j][i].z, angle_x);
			rotate_y_axis(&map->cells[j][i].x, &map->cells[j][i].z, angle_y);
			rotate_z_axis(&map->cells[j][i].x, &map->cells[j][i].y, angle_z);
			map->cells[j][i].x += map->info.center_x;
			map->cells[j][i].y += map->info.center_y;
			map->cells[j][i].z += map->info.center_z;
		}
	}
}
