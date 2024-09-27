/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_map_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:01:00 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/27 14:01:02 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	compute_center(t_map *map)
{
	int	i;
	int	j;

	map->info.min_x = map->cells[0][0].x;
	map->info.max_x = map->cells[0][0].x;
	map->info.min_y = map->cells[0][0].y;
	map->info.max_y = map->cells[0][0].y;
	map->info.min_z = map->cells[0][0].z;
	map->info.max_z = map->cells[0][0].z;
	j = -1;
	while (++j < map->y)
	{
		i = -1;
		while (++i < map->x)
		{
			if (map->cells[j][i].x < map->info.min_x)
				map->info.min_x = map->cells[j][i].x;
			if (map->cells[j][i].x > map->info.max_x)
				map->info.max_x = map->cells[j][i].x;
			if (map->cells[j][i].y < map->info.min_y)
				map->info.min_y = map->cells[j][i].y;
			if (map->cells[j][i].y > map->info.max_y)
				map->info.max_y = map->cells[j][i].y;
			if (map->cells[j][i].z < map->info.min_z)
				map->info.min_z = map->cells[j][i].z;
			if (map->cells[j][i].z > map->info.max_z)
				map->info.max_z = map->cells[j][i].z;
		}
	}
	map->info.center_x = (map->info.min_x + map->info.max_x) / 2;
	map->info.center_y = (map->info.min_y + map->info.max_y) / 2;
	map->info.center_z = (map->info.min_z + map->info.max_z) / 2;
}

void	rotate_x_axis(float *y, float *z, float angle)
{
	float	tmp_y;
	float	tmp_z;

	angle *= DEG;
	tmp_y = *y * cos(angle) - *z * sin(angle);
	tmp_z = *y * sin(angle) + *z * cos(angle);
	*y = tmp_y;
	*z = tmp_z;
}

void	rotate_y_axis(float *x, float *z, float angle)
{
	float	tmp_x;
	float	tmp_z;

	angle *= DEG;
	tmp_x = *x * cos(angle) + *z * sin(angle);
	tmp_z = -(*x) * sin(angle) + *z * cos(angle);
	*x = tmp_x;
	*z = tmp_z;
}

void	rotate_z_axis(float *x, float *y, float angle)
{
	float	tmp_x;
	float	tmp_y;

	angle *= DEG;
	tmp_x = *x * cos(angle) - *y * sin(angle);
	tmp_y = *x * sin(angle) + *y * cos(angle);
	*x = tmp_x;
	*y = tmp_y;
}
