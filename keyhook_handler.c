/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:09:56 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/28 15:09:57 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_tab(t_hook_params *hook_params)
{
	hook_params->transf = (hook_params->transf + 1) % 3;
	if (hook_params->transf == s_mode)
		ft_printf("Scaling mode\n");
	if (hook_params->transf == r_mode)
		ft_printf("Rotation mode\n");
	if (hook_params->transf == t_mode && !hook_params->centered)
		ft_printf("Translation mode\n");
	if (hook_params->transf == t_mode && hook_params->centered)
		ft_printf("Translating while centered won't be visible\n");
}

void	handle_space(t_hook_params *hook_params)
{
	hook_params->centered = !hook_params->centered;
	manual(hook_params, no_axis, 0);
}

void	handle_escape(t_hook_params *hook_params)
{
	mlx_delete_image(hook_params->mlx, hook_params->mlx_img);
	mlx_terminate(hook_params->mlx);
	ft_free(hook_params->map->y, (void **)hook_params->map->cells);
	exit(EXIT_SUCCESS);
}

void	handle_wasdqe(mlx_key_data_t keydata, t_hook_params *hook_params)
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
