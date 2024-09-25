/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 03:24:32 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/25 19:36:56 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	translate_map(t_map *map, float tx, float ty, float tz)
{
	int	j;
	int	i;

	j = -1;
	while (++j < map->y)
	{
		i = -1;
		while (++i < map->x)
		{
			map->cells[j][i].x += tx;
			map->cells[j][i].y += ty;
			map->cells[j][i].z += tz;
		}
	}
}

void	scale_map(t_map *map, float sx, float sy, float sz)
{
	int	j;
	int	i;

	j = -1;
	while (++j < map->y)
	{
		i = -1;
		while (++i < map->x)
		{
			map->cells[j][i].x *= sx;
			map->cells[j][i].y *= sy;
			map->cells[j][i].z *= sz;
		}
	}
}

void compute_center(t_map *map, float *center_x, float *center_y, float *center_z)
{
	float	min_x = map->cells[0][0].x;
	float	max_x = map->cells[0][0].x;
	float	min_y = map->cells[0][0].y;
	float	max_y = map->cells[0][0].y;
	float	min_z = map->cells[0][0].z;
	float	max_z = map->cells[0][0].z;
	int	i
	int	j;

	j = -1;
	while (++j < map->y)
	{
		i = -1;
		while (++i < map->x)
		{
			float x = map->cells[j][i].x;
			float y = map->cells[j][i].y;
			float z = map->cells[j][i].z;
			if (x < min_x) min_x = x;
			if (x > max_x) max_x = x;
			if (y < min_y) min_y = y;
			if (y > max_y) max_y = y;
			if (z < min_z) min_z = z;
			if (z > max_z) max_z = z;
		}
	}
	*center_x = (min_x + max_x) / 2;
	*center_y = (min_y + max_y) / 2;
	*center_z = (min_z + max_z) / 2;
}

void	rotate_map(t_map *map, float angle_x, float angle_y, float angle_z)
{
	int		j;
	int		i;
	float	x;
	float	y;
	float	z;
	float	tmp_x;
	float	tmp_y;
	float	tmp_z;

	angle_x *= DEG;
	angle_y *= DEG;
	angle_z *= DEG;

	float center_x;
	float center_y;
	float center_z;

	compute_center(map, &center_x, &center_y, &center_z);

	j = -1;
	while (++j < map->y)
	{
		i = -1;
		while (++i < map->x)
		{
			x = map->cells[j][i].x;
			y = map->cells[j][i].y;
			z = map->cells[j][i].z;

			x -= center_x;
			y -= center_y;
			z -= center_z;

			if (angle_x != 0)
			{
				tmp_y = y * cos(angle_x) - z * sin(angle_x);
				tmp_z = y * sin(angle_x) + z * cos(angle_x);
				y = tmp_y;
				z = tmp_z;
			}
			if (angle_y != 0)
			{
				tmp_x = x * cos(angle_y) + z * sin(angle_y);
				tmp_z = -x * sin(angle_y) + z * cos(angle_y);
				x = tmp_x;
				z = tmp_z;
			}
			if (angle_z != 0)
			{
				tmp_x = x * cos(angle_z) - y * sin(angle_z);
				tmp_y = x * sin(angle_z) + y * cos(angle_z);
				x = tmp_x;
				y = tmp_y;
			}

			x += center_x;
			y += center_y;
			z += center_z;

			map->cells[j][i].x = x;
			map->cells[j][i].y = y;
			map->cells[j][i].z = z;
		}
	}
}

