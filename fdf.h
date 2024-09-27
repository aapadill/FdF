/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:25:49 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/25 19:49:49 by aapadill         ###   ########.fr       */
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
# define CANVAS_SIZE WIDTH * HEIGHT

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define DEG M_PI / 180
# define ISO_ANG M_PI / 6


//enums
typedef enum e_axis
{
	x_axis = 0,
	y_axis = 1,
	z_axis = 2,
	no_axis = 3
}	t_axis;

typedef enum e_transf
{
	t_mode = 0,
	r_mode = 1,
	s_mode = 2,
	no_mode = 3
}	t_transf;

typedef enum e_step
{
	s_constant = 1,
	r_degrees = 2,
	t_pixels = 5,
}	t_step;

//structs
typedef struct s_cell
{
	float		x;
	float		y;
	float		z;
	uint32_t	color;
}	t_cell;

typedef struct s_map_info
{
	float		min_x;
	float		max_x;
	float		min_y;
	float		max_y;
	float		min_z;
	float		max_z;
	float 		center_x;
	float 		center_y;
	float 		center_z;
}	t_map_info;

typedef struct s_map
{
	t_map_info	info;
	int			x;
	int			y;
	t_cell		**cells;
}	t_map;

typedef struct s_pixel
{
	float		x;
	float		y;
	float		z;
	uint32_t	color;
}	t_pixel;

typedef struct s_image
{
	int		x;
	int		y;
	float	min_x;
	float	max_x;
	float	min_y;
	float	max_y;
	float	width;
	float	height;
	t_pixel	**pixels;
}	t_img;

typedef struct s_hook_params
{
	t_map		*map;
	mlx_t		*mlx;
	t_img		*img;
	mlx_image_t	*mlx_img;
	t_transf	transf;
	t_step		step;
	float		rx;
	float		ry;
	float		rz;
	float		tx;
	float		ty;
	float		tz;
	float		sx;
	float		sy;
	float		sz;
	int			centered;
}	t_hook_params;

//fdf_utils.c
void	mlx_perror(void);
int		ft_perror(char *error_msg, int is_syscall);
char	*clean(char *line);
void	ft_free(int n, void **ptr_array);

//parsing_utils.c
void	ft_reach_end(int n, void **ptr_array);
void	clear_map(t_map *map);
void	init_img(t_img *img, t_map *map);

//parsing.c
void	validate_values(char **values);
t_cell	**init_cells(int x, int y);
t_cell	**validate_file(char **argv, int *x, int *y);
void	insert_values(t_map *map, char **x_values, int y);
void	fill_cells(t_map *map, char **argv);

//line_utils.c
uint8_t		get_r(uint32_t rgba);
uint8_t		get_g(uint32_t rgba);
uint8_t		get_b(uint32_t rgba);
uint32_t	get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

//line.c
void	bresenham(mlx_image_t *img, t_pixel *start, t_pixel *end, float *depth);
void	put_img(mlx_image_t *mlx_img, t_img *img);

//transform_map_utils.c
void	compute_center(t_map *map);
void	rotate_x_axis(float *y, float *z, float angle);
void	rotate_y_axis(float *x, float *z, float angle);
void	rotate_z_axis(float *x, float *y, float angle);

//transform_map.c
void	translate_map(t_map *map, float tx, float ty, float tz);
void	scale_map(t_map *map, float sx, float sy, float sz);
void	rotate_map(t_map *map, float angle_x, float angle_y, float angle_z);

//keyhook_utils.c
float	*parameter_finder(t_hook_params *h_p, t_axis axis);
void	copy_map(t_map *dst, t_map *src);

//keyhook.c
void	display(mlx_t *mlx, t_map *map, mlx_image_t *mlx_img, int centered);
void	manual(t_hook_params *h_p, t_axis axis, char sign);
void	keyhook(mlx_key_data_t keydata, void *param);

//projection.c
void	update_img_info(t_img *img);
void	project_isometric(t_img *img, t_map *map);

//transform_image.c
void	scale_to_fit(t_img *img);
void	translate_to_fit(t_img *img);
void	scale_img(t_img *img, float sx, float sy);
void	translate_img(t_img *img, int tx, int ty);
void	rotate_img(t_img *img, float angle);

#endif