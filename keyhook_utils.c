/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:18:17 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/24 18:18:19 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void copy_map(t_map *dst, t_map *src)
{
	int i;
	int j;

	dst->x = src->x;
	dst->y = src->y;
	dst->z_min = src->z_min;
	dst->z_max = src->z_max;
	dst->cells = malloc(sizeof(t_cell *) * src->y);
	if (!dst->cells)
		ft_perror("Malloc error (copy_map)", 1);
	i = -1;
	while (++i < src->y)
	{
		dst->cells[i] = malloc(sizeof(t_cell) * src->x);
		if (!dst->cells[i])
		{
			ft_free(i, (void **)dst->cells);
			ft_perror("Malloc error (copy_map)", 1);
		}
		j = -1;
		while (++j < src->x)
			dst->cells[i][j] = src->cells[i][j];
	}
}

/*
 * First img projection without any map transformations
 */
void	display(mlx_t *mlx, t_map *map, mlx_image_t *mlx_img, int centered)
{
	t_img	img;
	
	init_img(&img, map);
	project_isometric(&img, map);
	update_img_info(&img);
	if (centered)
	{
		scale_to_fit(&img);
		translate_to_fit(&img);
	}
	else
		translate_img(&img, WIDTH/2, HEIGHT/2);
	ft_memset(mlx_img->pixels, 0, mlx_img->width * mlx_img->height * sizeof(int32_t));
	put_img(mlx_img, &img);
	ft_free(img.y, (void **)img.pixels);
	if (mlx_image_to_window(mlx, mlx_img, 0, 0) < 0)
		mlx_perror();
}
