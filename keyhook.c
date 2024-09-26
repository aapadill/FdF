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
 * Returns the address of the parameter to be modified, assumes:
 * 0) transformations are only rotation, translation and scaling
 * 1) x, y, z are defined in order in the t_hook_params struct 
 * 2) the axis are either 'x', 'y' or 'z' (only).
 */
float	*parameter_finder(t_hook_params	*h_p, t_axis axis)
{
	float	*ptr;

	ptr = NULL;
	if (axis < x_axis || axis > no_axis)
		ft_perror("Invalid axis", 0); //free everything
	if (h_p->transf == s_mode)
	{
		h_p->step = s_constant;
		ptr = &h_p->sx + axis;
	}
	if (h_p->transf == r_mode)
	{
		h_p->step = r_degrees;
		ptr = &h_p->rx + axis;
		if (*ptr >= 360)
			*ptr -= 360;
	}
	if (h_p->transf == t_mode)
	{
		h_p->step = t_pixels;
		ptr = &h_p->tx + axis;
	}
	if (!ptr)
		ft_perror("Invalid transformation mode", 0); //free everything
	return (ptr);
}

/*
 * Transforms the 3D map (using keyhooks) and then creates a 2D projection,
 * then, this 2D projection is copied to the canvas and displayed on the window
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
	update_img_info(&img);
	if (h_p->centered)
	{
		scale_to_fit(&img);
		translate_to_fit(&img);
	}
	else
		translate_img(&img, WIDTH/2, HEIGHT/2);
	ft_memset(h_p->mlx_img->pixels, 0, h_p->mlx_img->width * h_p->mlx_img->height * sizeof(int32_t));
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
