/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 03:24:32 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/13 03:27:44 by aapadill         ###   ########.fr       */
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

	j = -1;
	while (++j < map->y)
	{
		i = -1;
		while (++i < map->x)
		{
			x = map->cells[j][i].x;
			y = map->cells[j][i].y;
			z = map->cells[j][i].z;
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
			map->cells[j][i].x = x;
			map->cells[j][i].y = y;
			map->cells[j][i].z = z;
		}
	}
}

void	project_isometric(t_img *img, t_map *map)
{
	int		j;
	int		i;
	float	x;
	float	y;
	float	z;
	float	x_prime;
	float	y_prime;
	float	angle;

	angle = M_PI / 6; //30deg

	j = -1;
	while (++j < map->y)
	{
		i = -1;
		while (++i < map->x)
		{
			x = map->cells[j][i].x;
			y = map->cells[j][i].y;
			z = map->cells[j][i].z;

			x_prime = (x - y) * cos(angle);
			y_prime = (x + y) * sin(angle) - z;

			img->pixels[j][i].x = x_prime;
			img->pixels[j][i].y = y_prime;
			img->pixels[j][i].color = map->cells[j][i].color; //maybe is not needed
			if (j == 0 && i == 0)
			{
				img->min_x = x_prime;
				img->max_x = x_prime;
				img->min_y = y_prime;
				img->max_y = y_prime;
			}
			else
			{
				if (x_prime < img->min_x)
					img->min_x = x_prime;
				if (x_prime > img->max_x)
					img->max_x = x_prime;
				if (y_prime < img->min_y)
					img->min_y = y_prime;
				if (y_prime > img->max_y)
					img->max_y = y_prime;
			}
		}
	}
	img->width = img->max_x - img->min_x;
	img->height = img->max_y - img->min_y;
}

/*
void	update_img(t_img *img, t_map *map)
{
	int		j;
	int		i;
	float	x;
	float	y;

	j = -1;
	while (++j < map->y)
	{
		i = -1;
		while (++i < map->x)
		{
			x = map->cells[j][i].x;
			y = map->cells[j][i].y;

			img->pixels[j][i].x = x;
			img->pixels[j][i].y = y;
			img->pixels[j][i].color = map->cells[j][i].color; //maybe is not needed. again

			if (j == 0 && i == 0)
			{
				img->min_x = x;
				img->max_x = x;
				img->min_y = y;
				img->max_y = y;
			}
			else
			{
				if (x < img->min_x)
					img->min_x = x;
				if (x > img->max_x)
					img->max_x = x;
				if (y < img->min_y)
					img->min_y = y;
				if (y > img->max_y)
					img->max_y = y;
			}
		}
	}
	img->width = img->max_x - img->min_x;
	img->height = img->max_y - img->min_y;
}
*/

void	display(mlx_t *mlx, t_map *map, t_img *img, mlx_image_t *mlx_img)
{
	float	sx;
	float	sy;
	//mafloat	sz;
	int		s;

	int		tx;
	int		ty;
	//int 	tz;

	//float	rx;
	//float	ry;
	//float	rz;

	//sx = 1;
	//sy = 1;
	//sz = 1;

	//tx = 0;
	//ty = 0;
	//tz = 0;

	//rx = 0;
	//ry = 0;
	//rz = 0;

	//transformations to the map
	//scale_map(map, sx, sy, sz);
	//rotate_map(map, rx, ry, rz);
	//translate_map(map, tx, ty, tz);

	//manual isometric
	project_isometric(img, map);
	//update_img(img, map);

	//fit img to window
	sx = WIDTH / img->width;
	sy = HEIGHT / img->height;
	if (sx < sy)
		s = sx;
	else
		s = sy;
	scale_img(img, s, s);

	//center image
	tx = (WIDTH - img->width) / 2 - img->min_x;
	ty = (HEIGHT - img->height) / 2 - img->min_y;
	translate_img(img, tx, ty);

	//background
	ft_memset(mlx_img->pixels, 0, mlx_img->width * mlx_img->height * sizeof(int32_t));

	//put image to mlx_img
	put_img(mlx_img, img);

	if (mlx_image_to_window(mlx, mlx_img, 0, 0) < 0)
		error();
}