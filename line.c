/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:58:23 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/10 11:59:46 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void bresenham(mlx_image_t *img, t_pixel *start, t_pixel *end, int color)
{
	int x = (int)(start->x);
	int y = (int)(start->y);
	int x2 = (int)(end->x);
	int y2 = (int)(end->y);

	int dx = abs(x2 - x);
	int dy = abs(y2 - y);
	int sx = (x < x2) ? 1 : -1;
	int sy = (y < y2) ? 1 : -1;
	int err = dx - dy;

	int e2;

	while (1)
	{
		//draw pixel at (x, y)
		mlx_put_pixel(img, x, y, color);
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
