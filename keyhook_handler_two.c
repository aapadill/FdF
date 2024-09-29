/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook_handler_two.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 08:33:05 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/29 08:33:07 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	post_transform(t_img *img, t_hook_params *h_p)
{
	if (h_p->centered)
	{
		h_p->txx = 0;
		h_p->tyy = 0;
		h_p->s = 1;
		scale_to_fit(img);
		translate_to_fit(img);
	}
	if (!h_p->centered)
	{
		scale_img(img, h_p->s, h_p->s);
		translate_img(img, WIDTH / 2 + h_p->txx, HEIGHT / 2 + h_p->tyy);
	}
}

void	handle_post(mlx_key_data_t keydata, t_hook_params *hook_params)
{
	if (keydata.key == MLX_KEY_RIGHT)
		hook_params->txx += abs((int)hook_params->s);
	if (keydata.key == MLX_KEY_LEFT)
		hook_params->txx -= abs((int)hook_params->s);
	if (keydata.key == MLX_KEY_DOWN)
		hook_params->tyy += abs((int)hook_params->s);
	if (keydata.key == MLX_KEY_UP)
		hook_params->tyy -= abs((int)hook_params->s);
	if (keydata.key == MLX_KEY_Z)
		hook_params->s += 1.1;
	if (keydata.key == MLX_KEY_X)
		hook_params->s -= 1.1;
	manual(hook_params, no_axis, 0);
}
