/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:31:03 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/10 12:42:34 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int	round_value(float value)
{
	return ((int)(value + 0.5));
}

static void window_use(t_map *map, int *height, int *width)
{
	float proj_min_x;
	float proj_max_x;
	float proj_min_y;
	float proj_max_y;

	proj_min_x = (0 - map->y) * cos(M_PI / 6);
	proj_max_x = (map->x - 0) * cos(M_PI / 6);
	proj_min_y = (0 + 0) * sin(M_PI/6) - map->z_max;
	proj_max_y = (map->x + map->y) * sin(M_PI / 6) - map->z_min;
	*width = (proj_max_x - proj_min_x) + (2 * 10);
	*height = (proj_max_y - proj_min_y) + (2 * 10);
}

void	project(t_pixel **proj, int i, int j, int z)
{
	//isometric projection
	proj[j][i].x = (i - j) * cos(M_PI / 6); //30deg
	proj[j][i].y = (i + j) * sin(M_PI / 6) - z; //30deg
}

void	scale(t_map *map, t_pixel **proj, int i, int j)
{
	int		height;
	int		width;

	window_use(map, &height, &width);
	proj[j][i].x *= 1;//(WIDTH / width);
	proj[j][i].y *= 1;//(HEIGHT / height);
}

void	translate(t_pixel **proj, int i, int j)
{
	//hardcored translation
	proj[j][i].x = round_value(proj[j][i].x + (WIDTH / 2));
	proj[j][i].y = round_value(proj[j][i].y + (HEIGHT / 2));
}

//static void print_map(t_cell **map, mlx_image_t *img, int x, int y)
static void print_map(t_map *map, mlx_image_t *img)
{
	int		j;
	int		i;
	t_pixel	**proj;

	proj = init_img(map->x, map->y);
	//error handling
	j = -1;
	while (++j < map->y)
	{
		i = -1;
		while (++i < map->x)
		{
			project(proj, i, j, map->cells[j][i].z);
			scale(map, proj, i, j);
			translate(proj, i, j);
			if (proj[j][i].y < 0 || proj[j][i].x < 0)
				continue ;
			mlx_put_pixel(img, proj[j][i].x, proj[j][i].y, map->cells[j][i].color);
			if (i + 1 < map->x)
			{
				project(proj, i + 1, j, map->cells[j][i + 1].z);
				scale(map, proj, i + 1, j);
				translate(proj, i + 1, j);
				bresenham(img, &proj[j][i], &proj[j][i + 1], map->cells[j][i].color);
			}
			if (j + 1 < map->y)
			{
				project(proj, i, j + 1, map->cells[j + 1][i].z);
				scale(map, proj, i, j + 1);
				translate(proj, i, j + 1);
				bresenham(img, &proj[j][i], &proj[j + 1][i], map->cells[j][i].color);
			}
		}
	}
}

int main(int argc, char **argv)
{
	t_map		map;
	mlx_t		*mlx;
	mlx_image_t	*img;

	map.x = 0; //erasable
	map.y = 0;
	if (argc != 2)
		ft_perror("No valid arguments", 0);
	map.cells = validate_file(argv, &map.x, &map.y);
	fill_cells(&map, argv);

	//window
	mlx = mlx_init(WIDTH, HEIGHT, "fdf", true);
	if (!mlx)
		error();

	//image
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
		error();

	//background
	ft_memset(img->pixels, 127, img->width * img->height * sizeof(int32_t));

	//map
	print_map(&map, img);

	//display instance
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		error();

	//img translate
	img->instances[0].x += 0;
	img->instances[0].y += 0;

	mlx_loop(mlx);

	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
