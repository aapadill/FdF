/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:31:03 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/04 07:44:55 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <MLX42/MLX42.h>
#define WIDTH 1024
#define HEIGHT 1024

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

/*
static void print_map(t_cell **map, int x, int y)
{
	int j;
	int i;

	j = -1;
	while (++j < y)
	{
		printf("\n");
		i = -1;
		while (++i < x)
			printf("%li ", map[j][i].alpha);
	}
}
void paint_map(mlx_image_t *img)
{
	while
}
*/

int main(int argc, char **argv)
{
	int			x;
	int			y;
	t_cell		**map;
	mlx_t		*mlx;
	mlx_image_t	*img;

	x = 0; //erasable
	y = 0;
	if (argc != 2)
		ft_perror("No valid arguments", 0);
	map = validate_map(argv, &x, &y);
	fill_map(map, argv);
	//print_map(map, x, y);

	//window
	mlx = mlx_init(WIDTH, HEIGHT, "init", true);
	if (!mlx)
		error();

	//image
	img = mlx_new_image(mlx, 512, 512);
	if (!img)
		error();

	//white background
	ft_memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));

	//map


	//display instance
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		error();

	mlx_loop(mlx);

	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
