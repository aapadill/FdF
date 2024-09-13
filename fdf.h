/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:25:49 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/12 17:51:06 by aapadill         ###   ########.fr       */
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
# define WIDTH 1024
# define HEIGHT 1024

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef struct s_cell
{
	int			x;
	int			y;
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
	t_map	*map;
	mlx_image_t	*mlx_img;
	t_img	*transformed;
}	t_hook_params;

//fdf_utils.c
int		ft_perror(char *error_msg, int is_syscall);
char	*clean(char *line);

//map_parsing.c
//int		validate_values(char **values);
//t_cell	**init_cells(int x, int y);
t_cell	**validate_file(char **argv, int *x, int *y);
//void	insert_values(t_map *map, char **x_values, int y);
void	fill_cells(t_map *map, char **argv);
void	init_img(t_img *img, t_map *map);

//line.c
void	bresenham(mlx_image_t *img, t_pixel *start, t_pixel *end);

//algebra_utils.c
void	error(void);
int	round_value(float value);

/*algebra.c
void	isometric(t_img *img, int i, int j, int z);
t_img	*transform_map(t_map *map);
t_img	*new_img(int argc, char **argv);
void	display(mlx_t *mlx, t_img *transformed, mlx_image_t	*img);
*/

//transform_map.c
void	translate_map(t_map *map, float tx, float ty, float tz);
void	scale_map(t_map *map, float sx, float sy, float sz);
void	rotate_map(t_map *map, float angle_x, float angle_y, float angle_z);
void	project_isometric(t_img *img, t_map *map);
void	update_img(t_img *img, t_map *map);
void	display(mlx_t *mlx, t_map *map, t_img *img, mlx_image_t *mlx_img);

//transform_image.c
void	scale_img(t_img *img, int sx, int sy);
void	translate_img(t_img *img, int tx, int ty);
void    rotate_img(t_img *img, float angle);
void	put_img(mlx_image_t *mlx_img, t_img *img);

#endif
