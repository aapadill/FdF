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

void	bresenham_init(t_line *line, t_pixel *start, t_pixel *end)
{
	start->x = roundf(start->x);
	start->y = roundf(start->y);
	start->z = roundf(start->z);
	end->x = roundf(end->x);
	end->y = roundf(end->y);
	end->z = roundf(end->z);
	bresenham_helper(line, *start, *end);
	line->cur_r = get_r(start->color);
	line->cur_g = get_g(start->color);
	line->cur_b = get_b(start->color);
}

void	bresenham_helper(t_line *line, t_pixel start, t_pixel end)
{
	line->dx = abs((int)end.x - (int)start.x);
	line->dy = abs((int)end.y - (int)start.y);
	line->err = 0;
	line->e2 = 2 * line->err;
	if (start.x < end.x)
		line->sx = 1;
	else
		line->sx = -1;
	if (start.y < end.y)
		line->sy = 1;
	else
		line->sy = -1;
	line->steps = line->dy;
	if (line->dx > line->dy)
		line->steps = line->dx;
	if (!line->steps)
		line->steps = 1;
	line->dz_step = abs((int)end.z - (int)start.z) / line->steps;
	line->distance = sqrt(line->dx * line->dx + line->dy * line->dy);
	line->dr_step = (get_r(end.color) - get_r(start.color)) / line->distance;
	line->dg_step = (get_g(end.color) - get_g(start.color)) / line->distance;
	line->db_step = (get_b(end.color) - get_b(start.color)) / line->distance;
	line->da_step = 255 / line->distance;
}

void	bresenham(mlx_image_t *img, t_pixel start, t_pixel end, float *dep)
{
	int		i;
	t_line	line;

	bresenham_init(&line, &start, &end);
	i = -1;
	while (++i <= line.steps)
	{
		draw_pixel(img, &start, &line, dep);
		update_line(&line, &start);
		update_color(&line);
		update_depth(&line, &start);
	}
}

void	put_img(mlx_image_t *mlx_img, t_img *img)
{
	int		j;
	int		i;
	float	*d;

	d = init_depth();
	j = -1;
	while (++j < img->y)
	{
		i = -1;
		while (++i < img->x)
		{
			if (i + 1 < img->x)
				bresenham(mlx_img, img->pixels[j][i], img->pixels[j][i + 1], d);
			if (j + 1 < img->y)
				bresenham(mlx_img, img->pixels[j][i], img->pixels[j + 1][i], d);
		}
	}
	free(d);
}
