/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:25:49 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/10 12:03:01 by aapadill         ###   ########.fr       */
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
	int					z;
	unsigned long	color;
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
	unsigned long	color;
}	t_pixel;

int		ft_perror(char *error_msg, int is_syscall);
char	*clean(char *line);

t_cell	**init_cells(int x, int y);
t_pixel	**init_img(int x, int y);
int		validate_values(char **values);
t_cell	**validate_file(char **argv, int *x, int *y);
int		insert_values(t_map *map, char **x_values, int y);
void	fill_cells(t_map *map, char **argv);

void	bresenham(mlx_image_t *img, t_pixel *start, t_pixel *end, int color);

#endif
