/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:58:23 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/11 01:06:08 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void bresenham(mlx_image_t *img, t_pixel *start, t_pixel *end)
{
	int x;
	int y;
	int x2;
	int y2;
	int dx;
	int dy;
	int sx;
	int sy;
	int err;
	int e2;

	x = (int)(start->x);
	y = (int)(start->y);
	x2 = (int)(end->x);
	y2 = (int)(end->y);
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
	while (1)
	{
		mlx_put_pixel(img, x, y, end->color); //color hardcored
		//exit condition
		if (x == x2 && y == y2)
			break;
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
	}
}
