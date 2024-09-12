/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:31:03 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/12 03:18:37 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void display_keyhook(mlx_key_data_t keydata, void *param)
{
	t_hook_params	*hook_params;
	mlx_image_t		*img;

	hook_params = (t_hook_params *)param;
	if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
		img = display(hook_params->mlx, hook_params->transformed);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		mlx_delete_image(hook_params->mlx, img);
}

int main(int argc, char **argv)
{
	mlx_t	*mlx;
	t_img	*transformed;
	t_hook_params	hook_params;

	//window
	mlx = mlx_init(WIDTH, HEIGHT, "fdf", true);
	if (!mlx)
		error();

	//args to map, map to proj img, put pixels to mlx_img
	transformed = new_img(argc, argv);
	hook_params.mlx = mlx;
	hook_params.transformed = transformed;

	//hook
	mlx_key_hook(mlx, &display_keyhook, &hook_params);

	mlx_loop(mlx);
	//mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
