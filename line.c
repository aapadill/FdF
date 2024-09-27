/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:58:23 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/20 15:42:58 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void bresenham(mlx_image_t *img, t_pixel *start, t_pixel *end, float *depth)
{
	//line
	int		x;
	int		y;
	int		x2;
	int		y2;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;

	//color
	float	step;
	float	red_step;
	float	green_step;
	float	blue_step;
	float	current_red;
	float	current_green;
	float	current_blue;
	uint32_t	current_color;

	//depth
	int		total_steps;
	int		i;
	int		index;
	float	current_z;
	float	z_step;

	//line
	x = (int)roundf(start->x);
	y = (int)roundf(start->y);
	x2 = (int)roundf(end->x);
	y2 = (int)roundf(end->y);
	dx = abs(x2 - x);
	dy = abs(y2 - y);
	err = dx - dy;

	if (x < x2)
		sx = 1;
	else
		sx = -1;
	if (y < y2)
		sy = 1;
	else
		sy = -1;

	//color
	step = sqrt(dx * dx + dy * dy);
	red_step = (get_r(end->color) - get_r(start->color)) / step;
	green_step = (get_g(end->color) - get_g(start->color)) / step;
	blue_step = (get_b(end->color) - get_b(start->color)) / step;
	current_red = get_r(start->color);
	current_green = get_g(start->color);
	current_blue = get_b(start->color);

	//depth
	if (dx > dy)
		total_steps = dx;
	else
		total_steps = dy;

	if (total_steps == 0)
		total_steps = 1;

	z_step = (end->z - start->z) / total_steps;
	current_z = start->z;

	i = 0;

	while (i <= total_steps)
	{
		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		{
			index = y * WIDTH + x;
			if (current_z < depth[index])
			{
				depth[index] = current_z;
				current_color = get_rgba(current_red, current_green, current_blue, 255);
				mlx_put_pixel(img, x, y, current_color);
			}
		}
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}
		current_red += red_step;
		current_green += green_step; 
		current_blue += blue_step;
		current_z += z_step;
		i++;
	}
}

void	put_img(mlx_image_t *mlx_img, t_img *img)
{
	int	j;
	int	i;

	float	*depth;
	int		buffer_size;
	int		index;

	buffer_size = WIDTH * HEIGHT;
	depth = malloc(sizeof(float) * buffer_size);
	if (!depth)
		ft_perror("Malloc error (depth)", 1);
	index = 0;
	while (index < buffer_size)
	{
		depth[index] = (float)INT_MAX;
		index++;
	}

	j = -1;
	while (++j < img->y)
	{
		i = -1;
		while (++i < img->x)
		{
			if (i + 1 < img->x)
				bresenham(mlx_img, &img->pixels[j][i], &img->pixels[j][i + 1], depth);
			if (j + 1 < img->y)
				bresenham(mlx_img, &img->pixels[j][i], &img->pixels[j + 1][i], depth);
		}
	}
	free(depth);
}
