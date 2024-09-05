/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:31:03 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/05 21:01:54 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"
#include <MLX42/MLX42.h>
#define WIDTH 1024
#define HEIGHT 1024

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

static void print_map(t_cell **map, mlx_image_t *img, int x, int y)
{
	int j;
	int i;
	float x_prime;
	float y_prime;
	int screen_x;
	int screen_y;
	float step_x;
	float step_y;

	step_x = img->width / (x + y); //assuming cuadratic maps?
	step_y = img->height / (x + y); //same
	j = -1;
	while (++j < y)
	{
		i = -1;
		while (++i < x)
		{
			//isometric projection
			x_prime = (i - j) * cos(M_PI / 6); //cos(30deg)
			y_prime = (i + j) * sin(M_PI / 6) - map[j][i].z; //sin(30deg)

			//hardcored scale
			x_prime *= step_x; //hardcored
			y_prime *= step_y; //hardcored

			//hardcored translation
			x_prime += img->width / 2;
			y_prime += img->height / 2;

			//rounding decimal px to integer px
			screen_x = (int)(x_prime + 0.5);
			screen_y = (int)(y_prime + 0.5);
			if (map[j][i].alpha)
				mlx_put_pixel(img, screen_x, screen_y, map[j][i].alpha);
				//*(img->pixels + (j * img->width + i) * 4) = map[j][i].alpha;
		}
	}
}

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
	mlx = mlx_init(WIDTH, HEIGHT, "first try", true);
	if (!mlx)
		error();

	//image
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
		error();

	//background
	ft_memset(img->pixels, 127, img->width * img->height * sizeof(int32_t));

	//map
	print_map(map, img, x, y);

	//display instance
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		error();

	//scale?
	img->instances[0].x += 0;
	img->instances[0].y += 0;

	mlx_loop(mlx);

	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
