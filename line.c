/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:58:23 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/11 16:33:21 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int get_r(int rgba)
{
    //return ((rgba >> 24) & 0xFF);
    return ((rgba >> 16) & 0xFF);
}

int get_g(int rgba)
{
    //return ((rgba >> 16) & 0xFF);
    return ((rgba >> 8) & 0xFF);
}

int get_b(int rgba)
{
    //return ((rgba >> 8) & 0xFF);
    return (rgba & 0xFF);
}

int get_a(int rgba)
{
    //return (rgba & 0xFF);
    return ((rgba >> 24) & 0xFF);
}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
    //return (r << 16 | g << 8 | b);
    //return (a << 24 | r << 16 | g << 8 | b);
}

void bresenham(mlx_image_t *img, t_pixel *start, t_pixel *end)
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

	///*
	//color
	float	step;
	float	red_step;
	float	green_step;
	float	blue_step;
	float	current_red;
	float	current_green;
	float	current_blue;
	uint32_t	current_color;
	//*/

	//line
	x = (int)(start->x);
	y = (int)(start->y);
	x2 = (int)(end->x);
	y2 = (int)(end->y);
	dx = abs(x2 - x);
	dy = abs(y2 - y);
	err = dx - dy;

	///*
	//color
	step = sqrt(dx * dx + dy * dy);
	red_step = (get_r(end->color) - get_r(start->color)) / step;
	green_step = (get_g(end->color) - get_g(start->color)) / step;
	blue_step = (get_b(end->color) - get_b(start->color)) / step;
	current_red = get_r(start->color);
	current_green = get_g(start->color);
	current_blue = get_b(start->color);
	//*/

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
	/*
	int rgba = end->color; // or 0xFFFFFFFF in hexadecimal
    int red = get_r(rgba);
    int green = get_g(rgba);
    int blue = get_b(rgba);
    int alpha = get_a(rgba);

    printf("Red: %d, Green: %d, Blue: %d, Alpha: %d\n", red, green, blue, alpha);
	*/
		current_color = get_rgba(current_red, current_green, current_blue, 127);
		mlx_put_pixel(img, x, y, current_color);
		//exit condition
		if (x == x2 && y == y2)
			break;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
			current_red += red_step;
			current_green += green_step; 
			current_blue += blue_step;
		}
		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}
	}
}
