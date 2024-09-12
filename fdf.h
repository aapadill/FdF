/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:25:49 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/12 03:23:55 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "ft_printf/include/ft_printf.h"
# include <fcntl.h>
# include <stdio.h> //erase, grep printf
# include <errno.h>
# include <string.h>
# include <stdint.h> //erase?
# include <math.h>
# include <MLX42/MLX42.h>
# define WIDTH 512
# define HEIGHT 512

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef struct s_cell
{
	int			z;
	uint32_t	color;
}	t_cell;

typedef struct s_map
{
	int		x;
	int		y;
	int		z_min;
	int		z_max;
	t_cell	**cells;
}	t_map;

typedef struct s_pixel
{
	float			x;
	float			y;
	uint32_t	color;
}	t_pixel;

typedef struct s_image
{
	int		x;
	float	min_x;
	float	max_x;
	int		y;
	float	min_y;
	float	max_y;
	float	width;
	float	height;
	t_pixel	**pixels;
}	t_img;

typedef struct s_hook_params
{
	mlx_t	*mlx;
	t_img	*transformed;
}	t_hook_params;

//fdf_utils.c
int		ft_perror(char *error_msg, int is_syscall);
char	*clean(char *line);

//map_parsing.c
t_cell	**init_cells(int x, int y);
void	init_img(t_img *img, t_map *map);
int		validate_values(char **values);
t_cell	**validate_file(char **argv, int *x, int *y);
int		insert_values(t_map *map, char **x_values, int y);
void	fill_cells(t_map *map, char **argv);

//line.c
void	bresenham(mlx_image_t *img, t_pixel *start, t_pixel *end);

//algebra_utils.c
void	error(void);
int	round_value(float value);

//algebra.c
void	project(t_img *img, int i, int j, int z);
t_img	*transform_map(t_map *map);
void	scale_img(t_img *img, int s);
void	translate_img(t_img *img, int t);
void	print_img(mlx_image_t *mlx_img, t_img *img);
t_img	*new_img(int argc, char **argv);
mlx_image_t	*display(mlx_t *mlx, t_img *transformed);

#endif
