/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:31:03 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/21 16:14:33 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 * Returns the address of the parameter to be modified, assumes:
 * 0) transformations are only rotation, translation and scaling
 * 1) x, y, z are defined in order in the t_hook_params struct 
 * 2) the axis are either 'x', 'y' or 'z' (only).
 */
float	*parameter_finder(t_hook_params	*h_p, char transf, char axis)
{
	float	*base;
	int		axis_index;

	base = NULL;
	axis_index = axis - 'x';
	if (axis_index < 0 || axis_index > 2)
		ft_perror("Invalid axis", 0); //free everything
	if (transf == 'r')
		base = &h_p->rx;
	else if (transf == 't')
		base = &h_p->tx;
	else if (transf == 's')
		base = &h_p->sx;
	if (base)
		return (base + axis_index);
	return (NULL);
}

void	action(t_hook_params *h_p, char transf, char axis, char sign)
{
	t_map	transformed_map;

	if (sign == '+')
		*parameter_finder(h_p, transf, axis) += 1;
	else
		*parameter_finder(h_p, transf, axis) -= 1;
	//printf("x: %f\n", h_p->rx);
	copy_map(&transformed_map, h_p->map);
	scale_map(&transformed_map, h_p->sx, h_p->sy, h_p->sz);
	rotate_map(&transformed_map, h_p->rx, h_p->ry, h_p->rz);
	translate_map(&transformed_map, h_p->tx, h_p->ty, h_p->tz);
	display(h_p->mlx, &transformed_map, h_p->mlx_img);
	ft_free(transformed_map.y, (void **)transformed_map.cells);
}

void	keyhook(mlx_key_data_t keydata, void *param)
{
	t_hook_params	*hook_params;

	hook_params = (t_hook_params *)param;
	if (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_X)
			action(hook_params, 'r', 'x', '+');
		if (keydata.key == MLX_KEY_S)
			action(hook_params, 'r', 'x', '-');
		if (keydata.key == MLX_KEY_C)
			action(hook_params, 'r', 'y', '+');
		if (keydata.key == MLX_KEY_D)
			action(hook_params, 'r', 'y', '-');
		if (keydata.key == MLX_KEY_Z)
			action(hook_params, 'r', 'z', '+');
		if (keydata.key == MLX_KEY_A)
			action(hook_params, 'r', 'z', '-');
		if (keydata.key == MLX_KEY_V)
			action(hook_params, 's', 'x', '+');
		if (keydata.key == MLX_KEY_F)
			action(hook_params, 's', 'x', '-');
		if (keydata.key == MLX_KEY_B)
			action(hook_params, 's', 'y', '+');
		if (keydata.key == MLX_KEY_G)
			action(hook_params, 's', 'y', '-');
		if (keydata.key == MLX_KEY_N)
			action(hook_params, 's', 'z', '+');
		if (keydata.key == MLX_KEY_H)
			action(hook_params, 's', 'z', '-');
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_delete_image(hook_params->mlx, hook_params->mlx_img);
		mlx_terminate(hook_params->mlx);
		ft_free(hook_params->map->y, (void **)hook_params->map->cells);
		exit(EXIT_SUCCESS);
	}
}

/*
 * Scales the projection to fit the window

static void	scale_to_fit(t_img *img)
{
	float	sx;
	float	sy;
	float	s;

	sx = WIDTH / img->width;
	sy = HEIGHT / img->height;
	if (sx < sy)
		s = sx;
	else
		s = sy;
	scale_img(img, s, s);
} */

/*
 * Translates the projection to the center of the window
 */
static void	translate_to_fit(t_img *img)
{
	int		tx;
	int		ty;
	tx = (WIDTH - img->width) / 2 - img->min_x;
	ty = (HEIGHT - img->height) / 2 - img->min_y;
	translate_img(img, tx, ty);
}

void	display(mlx_t *mlx, t_map *map, mlx_image_t *mlx_img)
{
	t_img	*img;
	t_img	img_local;

	img = &img_local;
	init_img(img, map);
	project_isometric(img, map);

	//scale proj to fit to window
	//scale_to_fit(img);

	//translate proj to fit to window
	translate_to_fit(img);

	//background
	ft_memset(mlx_img->pixels, 0, mlx_img->width * mlx_img->height * sizeof(int32_t));

	//put image to mlx_img
	put_img(mlx_img, img);

	ft_free(img->y, (void **)img->pixels);

	if (mlx_image_to_window(mlx, mlx_img, 0, 0) < 0)
		mlx_perror();
}

void	init_hook_params(t_hook_params *hook_params, t_map *map)
{
	hook_params->rx = 0;
	hook_params->ry = 0;
	hook_params->rz = 0;
	hook_params->tx = 0;
	hook_params->ty = 0;
	hook_params->tz = 0;
	hook_params->sx = 1;
	hook_params->sy = 1;
	hook_params->sz = 1;
	//hook_params->map = map;
	hook_params->mlx = mlx_init(WIDTH, HEIGHT, "fdf", true);
	if (!hook_params->mlx)
		mlx_perror();
	hook_params->mlx_img = mlx_new_image(hook_params->mlx, WIDTH, HEIGHT);
	if (!hook_params->mlx_img)
		mlx_perror(); //free mlx
	hook_params->map = map;
}

int main(int argc, char **argv)
{
	t_map			map;
	t_hook_params	hook_params;

	map.y = 0;
	if (argc != 2)
		ft_perror("No valid arguments", 0);
	map.cells = validate_file(argv, &map.x, &map.y);
	fill_cells(&map, argv);
	init_hook_params(&hook_params, &map);
	display(hook_params.mlx, &map, hook_params.mlx_img);
	mlx_key_hook(hook_params.mlx, &keyhook, &hook_params);
	mlx_loop(hook_params.mlx);
	ft_free(map.y, (void **)map.cells);
	mlx_delete_image(hook_params.mlx, hook_params.mlx_img);
	mlx_terminate(hook_params.mlx);
	return (EXIT_SUCCESS);
}
