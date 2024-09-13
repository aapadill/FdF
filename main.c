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
	if (keydata.key == MLX_KEY_X && keydata.action == MLX_PRESS)
	{
		rotate_map(hook_params->map, M_PI / 90, 0, 0);
		display(hook_params->mlx, hook_params->map, hook_params->transformed, hook_params->mlx_img);
	}
	if (keydata.key == MLX_KEY_Y && keydata.action == MLX_PRESS)
	{
		rotate_map(hook_params->map, 0, M_PI / 90, 0);
		display(hook_params->mlx, hook_params->map, hook_params->transformed, hook_params->mlx_img);
	}
	if (keydata.key == MLX_KEY_Z && keydata.action == MLX_PRESS)
	{
		rotate_map(hook_params->map, 0, 0, M_PI / 90);
		display(hook_params->mlx, hook_params->map, hook_params->transformed, hook_params->mlx_img);
	}
	if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
	{
		scale_map(hook_params->map, 0.5, 0.5, 0.5);
		display(hook_params->mlx, hook_params->map, hook_params->transformed, hook_params->mlx_img);
	}
	if (keydata.key == MLX_KEY_2 && keydata.action == MLX_PRESS)
	{
		scale_map(hook_params->map, 2, 2, 2);
		display(hook_params->mlx, hook_params->map, hook_params->transformed, hook_params->mlx_img);
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		return ;
	}
}

/*
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
*/

int main(int argc, char **argv)
{
	mlx_t	*mlx;
	t_map	map;
	t_img	*transformed;
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

	//initialize transformed
	transformed = malloc(sizeof(t_img));
	if (!transformed)
		ft_perror("Malloc error (t_img)", 1);
	init_img(transformed, &map);

	//first display
	mlx_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	hook_params.mlx_img = mlx_img;
	if (!mlx_img)
		error();
	
	//hardcode isometric projection (only the first time)
	project_isometric(transformed, &map);

	//display it
	display(mlx, &map, transformed, mlx_img);
	hook_params.transformed = transformed;

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