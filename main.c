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

/* 
 * change the naming to transform_keyhook and
 * make this one more general so inside param there's also a
 * pointer to transformation functions: scale, translate, rotate
*/
void display_keyhook(mlx_key_data_t keydata, void *param)
{
	t_hook_params	*hook_params;

	hook_params = (t_hook_params *)param;
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
		display(hook_params->mlx, hook_params->transformed, hook_params->mlx_img);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		return ;
	}
}

int main(int argc, char **argv)
{
	mlx_t	*mlx;
	mlx_image_t *mlx_img;
	t_img	*transformed;
	t_hook_params	hook_params;

	//window
	mlx = mlx_init(WIDTH, HEIGHT, "fdf", true);
	if (!mlx)
		error();
	hook_params.mlx = mlx;

	//args to map -> map to img -> pixels of img to mlx_img
	transformed = new_img(argc, argv);
	hook_params.transformed = transformed;

	//first display
	mlx_img = mlx_new_image(mlx, WIDTH, HEIGHT); //transformed->width, transformed->height
	hook_params.mlx_img = mlx_img;
	if (!mlx_img)
		error();
	display(mlx, transformed, mlx_img);

	//hook
	mlx_key_hook(mlx, &display_keyhook, &hook_params);

	//display instance
	if (mlx_image_to_window(mlx, mlx_img, 0, 0) < 0)
		error();

	mlx_loop(mlx);
	mlx_delete_image(mlx, mlx_img);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
