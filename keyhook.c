/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:35:39 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/25 19:55:56 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 * First img projection without any map transformations
 */
void	display(mlx_t *mlx, t_map *map, mlx_image_t *mlx_img, int centered)
{
	t_img	img;

	init_img(&img, map);
	project_isometric(&img, map);
	if (centered)
	{
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
	project_isometric(&img, &transformed_map);
	if (h_p->centered)
		scale_to_fit(&img);
	if (h_p->centered)
		translate_to_fit(&img);
	else
		translate_img(&img, WIDTH / 2, HEIGHT / 2);
	ft_memset(h_p->mlx_img->pixels, 0, CANVAS_SIZE * sizeof(int32_t));
	put_img(h_p->mlx_img, &img);
	if (mlx_image_to_window(h_p->mlx, h_p->mlx_img, 0, 0) < 0)
		mlx_perror();
	ft_free(img.y, (void **)img.pixels);
	ft_free(transformed_map.y, (void **)transformed_map.cells);
}

/*
 * Map / projection transformer using user keydata input
 */
void	keyhook(mlx_key_data_t keydata, void *param)
{
	t_hook_params	*hook_params;

	hook_params = (t_hook_params *)param;
	if (keydata.key == MLX_KEY_TAB && keydata.action == MLX_PRESS)
	{
		hook_params->transf = (hook_params->transf + 1) % 3;
		if (hook_params->transf == s_mode)
			ft_printf("Scaling mode\n");
		if (hook_params->transf == r_mode)
			ft_printf("Rotation mode\n");
		if (hook_params->transf == t_mode && !hook_params->centered)
			ft_printf("Translation mode\n");
		if (hook_params->transf == t_mode && hook_params->centered)
			ft_printf("Translation mode not available while centered\n");
	}
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		hook_params->centered = !hook_params->centered;
		manual(hook_params, no_axis, 0);
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_delete_image(hook_params->mlx, hook_params->mlx_img);
		mlx_terminate(hook_params->mlx);
		ft_free(hook_params->map->y, (void **)hook_params->map->cells);
		exit(EXIT_SUCCESS);
	}
	if (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_W)
			manual(hook_params, y_axis, '+');
		if (keydata.key == MLX_KEY_S)
			manual(hook_params, y_axis, '-');
		if (keydata.key == MLX_KEY_D)
			manual(hook_params, x_axis, '+');
		if (keydata.key == MLX_KEY_A)
			manual(hook_params, x_axis, '-');
		if (keydata.key == MLX_KEY_E)
			manual(hook_params, z_axis, '+');
		if (keydata.key == MLX_KEY_Q)
			manual(hook_params, z_axis, '-');
	}
}
