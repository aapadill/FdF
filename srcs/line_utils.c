/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:07:13 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/08 15:47:24 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_pixel(mlx_image_t *img, t_pixel *px, t_line *line, float *dep)
{
	int			index;
	uint32_t	color;

	if (px->x >= 0 && px->x < WIDTH && px->y >= 0 && px->y < HEIGHT)
	{
		index = (int)px->y * WIDTH + (int)px->x;
		if (px->z < dep[index])
		{
			color = get_rgba(line->cur_r, line->cur_g, line->cur_b, NO_ALPHA);
			dep[index] = px->z;
			mlx_put_pixel(img, px->x, px->y, color);
		}
	}
}

void	update_line(t_line *line, t_pixel *start)
{
	line->e2 = 2 * line->err;
	if (line->e2 > -line->dy)
	{
		line->err -= line->dy;
		start->x += line->sx;
	}
	if (line->e2 < line->dx)
	{
		line->err += line->dx;
		start->y += line->sy;
	}
}

void	update_color(t_line *line)
{
	line->cur_r += line->dr_step;
	line->cur_g += line->dg_step;
	line->cur_b += line->db_step;
}

void	update_depth(t_line *line, t_pixel *start)
{
	start->z += line->dz_step;
}

void	init_depth(float **depth)
{
	int	index;

	index = 0;
	*depth = gc_alloc(sizeof(float) * CANVAS_SIZE);
	if (!*depth)
		gc_perror("Malloc depth error", 1);
	while (index < CANVAS_SIZE)
	{
		(*depth)[index] = (float)INT_MAX;
		index++;
	}
}
