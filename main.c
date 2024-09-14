/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:31:03 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/12 17:27:20 by aapadill         ###   ########.fr       */
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
	i = 0;
	while (i < src->y)
	{
		dst->cells[i] = malloc(sizeof(t_cell) * src->x);
		if (!dst->cells[i])
		{
			while (--i >= 0)
				free(dst->cells[i]);
			free(dst->cells);
			ft_perror("Malloc error (copy_map)", 1);
		}
		j = 0;
		while (j < src->x)
		{
			dst->cells[i][j] = src->cells[i][j];
			j++;
		}
		i++;
	}
}

void	display(mlx_t *mlx, t_map *map, mlx_image_t *mlx_img)
{
	float	sx;
	float	sy;
	int		s;

	int		tx;
	int		ty;

	int i;
	t_img *img;
	t_img img_local;

	img = &img_local;

	//scale_map(map, sx, sy, sz);
	//rotate_map(map, rx, ry, rz);
	//translate_map(map, tx, ty, tz);

	init_img(img, map);
	project_isometric(img, map);

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

	i = img->y;
	while (i--)
		free(img->pixels[i]);
	free(img->pixels);

	if (mlx_image_to_window(mlx, mlx_img, 0, 0) < 0)
		error();
}

/* 
 * change the naming to transform_keyhook and
 * make this one more general so inside param there's also a
 * pointer to transformation functions: scale, translate, rotate
*/
void display_keyhook(mlx_key_data_t keydata, void *param)
{
	t_hook_params	*hook_params;
	int i;

	hook_params = (t_hook_params *)param;
	if (keydata.key == MLX_KEY_X && keydata.action == MLX_PRESS)
	{
		t_map	transformed_map;

		hook_params->rx += M_PI / 180;
		
		printf("%f\n", hook_params->rx / (M_PI / 180));
		copy_map(&transformed_map, hook_params->map);
		rotate_map(&transformed_map, hook_params->rx, hook_params->ry, hook_params->rz);
		display(hook_params->mlx, &transformed_map, hook_params->mlx_img);
		i = transformed_map.y;
		while (i--)
			free(transformed_map.cells[i]);
		free(transformed_map.cells);
	}
	if (keydata.key == MLX_KEY_Y && keydata.action == MLX_PRESS)
	{
		t_map	transformed_map;

		hook_params->ry += M_PI / 180;
		
		printf("%f\n", hook_params->ry / (M_PI / 180));
		copy_map(&transformed_map, hook_params->map);
		rotate_map(&transformed_map, hook_params->rx, hook_params->ry, hook_params->rz);
		display(hook_params->mlx, &transformed_map, hook_params->mlx_img);
		i = transformed_map.y;
		while (i--)
			free(transformed_map.cells[i]);
		free(transformed_map.cells);
	}
	if (keydata.key == MLX_KEY_Z && keydata.action == MLX_PRESS)
	{
		t_map	transformed_map;

		hook_params->rz += M_PI / 180;
		
		printf("%f\n", hook_params->rz / (M_PI / 180));
		copy_map(&transformed_map, hook_params->map);
		rotate_map(&transformed_map, hook_params->rx, hook_params->ry, hook_params->rz);
		display(hook_params->mlx, &transformed_map, hook_params->mlx_img);
		i = transformed_map.y;
		while (i--)
			free(transformed_map.cells[i]);
		free(transformed_map.cells);
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_delete_image(hook_params->mlx, hook_params->mlx_img);
		mlx_terminate(hook_params->mlx);

		i = hook_params->map->y;
		while (i--)
			free(hook_params->map->cells[i]);
		free(hook_params->map->cells);
		exit(EXIT_SUCCESS);
	}
}

int main(int argc, char **argv)
{
	mlx_t	*mlx;
	t_map	map;
	mlx_image_t *mlx_img;
	t_hook_params	hook_params;
	int		i;

	//map
	map.y = 0;
	if (argc != 2)
		ft_perror("No valid arguments", 0);
	map.cells = validate_file(argv, &map.x, &map.y);
	fill_cells(&map, argv);
	hook_params.map = &map;

	//window
	mlx = mlx_init(WIDTH, HEIGHT, "fdf", true);
	if (!mlx)
		error();
	hook_params.mlx = mlx;

	//canvas
	mlx_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!mlx_img)
		error();
	hook_params.mlx_img = mlx_img;

	hook_params.rx = 0;
	hook_params.ry = 0;
	hook_params.rz = 0;

	//
	display(mlx, &map, mlx_img);

	//hook
	mlx_key_hook(mlx, &display_keyhook, &hook_params);

	//display instance
	if (mlx_image_to_window(mlx, mlx_img, 0, 0) < 0)
		error();

	mlx_loop(mlx);
	mlx_delete_image(mlx, mlx_img);
	mlx_terminate(mlx);

	i = map.y;
	while (i--)
		free(map.cells[i]);
	free(map.cells);

	return (EXIT_SUCCESS);
}