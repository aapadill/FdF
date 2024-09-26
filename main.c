/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:31:03 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/25 19:42:13 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_hook_params(t_hook_params *hook_params, t_map *map)
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
	hook_params->centered = 1;
	hook_params->transf = r_mode;
	ft_printf("Rotation mode\n");
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
	if (map.y < 10 || map.x < 10)
		scale_map(&map, 5, 5, 5);
	init_hook_params(&hook_params, &map);
	display(hook_params.mlx, &map, hook_params.mlx_img, hook_params.centered);
	mlx_key_hook(hook_params.mlx, &keyhook, &hook_params);
	mlx_loop(hook_params.mlx);
	ft_free(map.y, (void **)map.cells);
	mlx_delete_image(hook_params.mlx, hook_params.mlx_img);
	mlx_terminate(hook_params.mlx);
	return (EXIT_SUCCESS);
}
