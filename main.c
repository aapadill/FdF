/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:31:03 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/09 14:14:10 by aapadill         ###   ########.fr       */
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

int	round_value(float value)
{
	return ((int)(value + 0.5));
}

void	project(t_pixel **proj, int i, int j, int z)
{
	//isometric projection
	proj[j][i].x = (i - j) * cos(M_PI / 6); //30deg
	proj[j][i].y = (i + j) * sin(M_PI / 6) - z; //30deg
}

void	scale(t_pixel **proj, int i, int j)
{
	proj[j][i].x *= 5;
	proj[j][i].y *= 5;
}

void	translate(t_pixel **proj, int i, int j)
{
	//hardcored translation
	proj[j][i].x = round_value(proj[j][i].x + (WIDTH / 2));
	proj[j][i].y = round_value(proj[j][i].y + (HEIGHT / 4));
}

void bresenham(mlx_image_t *img, t_pixel *start, t_pixel *end, int color)
{
	int x = (int)(start->x);
	int y = (int)(start->y);
	int x2 = (int)(end->x);
	int y2 = (int)(end->y);

	int dx = abs(x2 - x);
	int dy = abs(y2 - y);
	int sx = (x < x2) ? 1 : -1;
	int sy = (y < y2) ? 1 : -1;
	int err = dx - dy;

	int e2;

	while (1)
	{
		//draw pixel at (x, y)
		mlx_put_pixel(img, x, y, color);
		//exit condition
		if (x == x2 && y == y2)
			break;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}
	}
}

static void print_map(t_cell **map, mlx_image_t *img, int x, int y)
{
	int		j;
	int		i;
	t_pixel	**proj;

	proj = init_img(x, y);
	//error handling
	j = -1;
	while (++j < y)
	{
		i = -1;
		while (++i < x)
		{
			project(proj, i, j, map[j][i].z);
			scale(proj, i, j);
			translate(proj, i, j);
			if (proj[j][i].y < 0 || proj[j][i].x < 0)
				continue ;
			mlx_put_pixel(img, proj[j][i].x, proj[j][i].y, map[j][i].color);
			if (i + 1 < x)
			{
				project(proj, i + 1, j, map[j][i + 1].z);
				scale(proj, i + 1, j);
				translate(proj, i + 1, j);
				bresenham(img, &proj[j][i], &proj[j][i + 1], map[j][i].color);
			}
			if (j + 1 < y)
			{
				project(proj, i, j + 1, map[j + 1][i].z);
				scale(proj, i, j + 1);
				translate(proj, i, j + 1);
				bresenham(img, &proj[j][i], &proj[j + 1][i], map[j][i].color);
			}
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
	print_map(map, img, x, y);

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
