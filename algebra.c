/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebra.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:52:45 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/12 17:53:56 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric(t_img *img, int i, int j, int z)
{
	//hardcoded isometric projection
	img->pixels[j][i].x = (i - j) * cos(M_PI / 6); //30deg
	img->pixels[j][i].y = (i + j) * sin(M_PI / 6) - z; //30deg

	if (!j && !i)
	{
		img->min_x = img->pixels[j][i].x;
		img->max_x = img->pixels[j][i].x;
		img->min_y = img->pixels[j][i].y;
		img->max_y = img->pixels[j][i].y;
	}
	if (img->pixels[j][i].x < img->min_x)
		img->min_x = img->pixels[j][i].x;
	if (img->pixels[j][i].x > img->max_x)
		img->max_x = img->pixels[j][i].x;
	if (img->pixels[j][i].y < img->min_y)
		img->min_y = img->pixels[j][i].y;
	if (img->pixels[j][i].y > img->max_y)
		img->max_y = img->pixels[j][i].y;
	img->width = img->max_x - img->min_x;
	img->height = img->max_y - img->min_y;
}

t_img	*transform_map(t_map *map)
{
	int		j;
	int		i;
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		ft_perror("Malloc error (t_img)", 1);
	init_img(img, map);
	j = -1;
	while (++j < img->y)
	{
		i = -1;
		while (++i < img->x)
			isometric(img, i, j, map->cells[j][i].z);
	}
	return (img);
}

t_img	*new_img(int argc, char **argv)
{
	t_map	map;
	t_img	*img;
	int		i;

	map.y = 0;
	if (argc != 2)
		ft_perror("No valid arguments", 0);
	map.cells = validate_file(argv, &map.x, &map.y);
	fill_cells(&map, argv);
	img = transform_map(&map);
	i = map.y;
	while (i--)
		free(map.cells[i]);
	free(map.cells);
	return (img);
}

void	display(mlx_t *mlx, t_img *transformed, mlx_image_t *img)
{
	int	sx;
	int	sy;
	//int	tx;
	//int	ty;

	//scale
	sx = 1;
	sy = 1;
	//s = round_value(WIDTH / transformed->width);
	//if (round_value(HEIGHT / transformed->height) < s)
	//	s = round_value(HEIGHT / transformed->height);
	scale_img(transformed, sx, sy);

	//translate
	//tx = round_value(transformed->width / 2);
	//ty = round_value(transformed->height / 2);
	translate_img(transformed, 10, 10);

	rotate_img(transformed, M_PI / 180);

	//background
	ft_memset(img->pixels, 0, img->width * img->height * sizeof(int32_t));

	//from transformed to mlx_img
	put_img(img, transformed);

	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		error();
}
