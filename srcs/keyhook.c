/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:35:39 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/07 17:32:57 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 * First img projection without any map transformations
 */
int	display(mlx_t *mlx, t_map *map, mlx_image_t *mlx_img, int centered)
{
	t_img	img;

	if (init_img(&img, map) == -1)
		return (-1);
	project_isometric(&img, map);
	if (centered)
	{
		ft_printf("Centered on\n");
		scale_to_fit(&img);
		translate_to_fit(&img);
	}
	else
		translate_img(&img, WIDTH / 2, HEIGHT / 2);
	ft_memset(mlx_img->pixels, 0, CANVAS_SIZE * sizeof(int32_t));
	put_img(mlx_img, &img);
	ft_free(img.y, (void **)img.pixels);
	if (mlx_image_to_window(mlx, mlx_img, 0, 0) < 0)
		mlx_perror();
	return (0);
}

/*
 * Transforms the 3D map (using keyhooks) and then creates a 2D projection,
 * then, this 2D projection is copied to the canvas and displayed on the window
 * improv: change CANVAS_SIZE for h_p->mlx_img->width and height
 */
void	manual(t_hook_params *h_p, t_axis axis, char sign)
{
	t_map	transformed_map;
	t_img	img;

	if (sign == '+')
		*parameter_finder(h_p, axis) += h_p->step;
	if (sign == '-')
		*parameter_finder(h_p, axis) -= h_p->step;
	copy_map(&transformed_map, h_p->map);
	scale_map(&transformed_map, h_p->sx, h_p->sy, h_p->sz);
	rotate_map(&transformed_map, h_p->rx, h_p->ry, h_p->rz);
	translate_map(&transformed_map, h_p->tx, h_p->ty, h_p->tz);
	init_img(&img, &transformed_map);
	project(&img, &transformed_map, h_p->projec);
	post_transform(&img, h_p);
	ft_memset(h_p->mlx_img->pixels, 0, CANVAS_SIZE * sizeof(int32_t));
	put_img(h_p->mlx_img, &img);
	if (mlx_image_to_window(h_p->mlx, h_p->mlx_img, 0, 0) < 0)
		mlx_perror();
	ft_free(img.y, (void **)img.pixels);
	ft_free(transformed_map.y, (void **)transformed_map.cells);
}

void	close_hook(void *param)
{
	t_hook_params	*hook_params;

	hook_params = (t_hook_params *)param;
	mlx_delete_image(hook_params->mlx, hook_params->mlx_img);
	mlx_terminate(hook_params->mlx);
	ft_free(hook_params->map->y, (void **)hook_params->map->cells);
	exit(EXIT_SUCCESS);
}

/*
 * Map or projection transformer using user keydata input
 */
void	keyhook(mlx_key_data_t keydata, void *param)
{
	t_hook_params	*hook_params;

	hook_params = (t_hook_params *)param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_TAB)
			handle_tab(hook_params);
		if (keydata.key == MLX_KEY_SPACE)
			handle_space(hook_params);
		if (keydata.key == MLX_KEY_ESCAPE)
			close_hook(hook_params);
		if (keydata.key == MLX_KEY_1
			|| keydata.key == MLX_KEY_2
			|| keydata.key == MLX_KEY_3)
			handle_numbers(keydata.key, hook_params);
	}
	if (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS)
	{
		handle_wasdqe(keydata, hook_params);
		handle_post(keydata, hook_params);
	}
}
