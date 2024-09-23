/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:40:45 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/20 15:52:25 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	validate_values(char **values)
{
	char	**z;
	int		color;
	int		i;

	i = 0;
	while (values[i])
	{
		z = ft_split(values[i], ',', &color);
		if (!z)
		{
			//close(fd); but you dont have it
			while(values[++i])
				 ;
			ft_free(i, (void**)values);
			ft_perror("Malloc error (z split)", 1);
		}
		if (color < 1 || color > 2 || int_overflows(z[0]))
		{
			while(values[++i])
				 ;
			ft_free(i, (void**)values);
			ft_free(color, (void **)z);
			ft_perror("Values format error", 0);
		}
		ft_free(color, (void **)z);
		i++;
	}
	return (1);
}

static t_cell	**init_cells(int x, int y)
{
	t_cell	**cells;
	int i;

	i = 0;
	cells = (t_cell **)malloc(sizeof(t_cell *) * y);
	if (!cells)
		ft_perror("Malloc error for cells", 1);
	while (i < y)
	{
		cells[i] = (t_cell *)malloc(sizeof(t_cell) * x);
		if (!cells[i])
		{
			ft_free(i, (void **)cells);
			ft_perror("Malloc error for a map row", 1);
		}
		i++;
	}
	return (cells);
}

/*
 * Validate the file and return a 2D array of cells
 */
t_cell	**validate_file(char **argv, int *x, int *y)
{
	int		fd;
	char	*line;
	int		values;
	char	**splitted_line;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_perror("No file", 1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		splitted_line = ft_split(clean(line), ' ', &values);
		free(line);
		if (!splitted_line)
		{
			close(fd);
			ft_perror("Malloc error (x split)", 1);
		}
		validate_values(splitted_line);
		if (!*y)
			*x = values;
		else if (*x != values)
		{
			close(fd);
			ft_free(values, (void **)splitted_line);
			ft_perror("Map error (your file is missing some x values)", 0);
		}
		(*y)++;
		ft_free(values, (void **)splitted_line);
	}
	close(fd);
	return (init_cells(*x, *y));
}

static	void	insert_values(t_map	*map, char **x_values, int y)
{
	int		i;
	char	**z;
	int		color;

	i = 0;
	while (x_values[i])
	{
		z = ft_split(x_values[i], ',', &color);
		if (!z)
		{
			//close(fd); but you dont have fd
			while (x_values[++i])
				 ;
			ft_free(i, (void **)x_values);
			ft_perror("Malloc error (z split)", 1);
		}
		map->cells[y][i].x = i;
		map->cells[y][i].y = y;
		map->cells[y][i].z = ft_atoi(z[0]);
		if (!i && !y)
		{
			map->z_min = map->cells[0][0].z;
			map->z_max = map->cells[0][0].z;
		}
		if (map->cells[y][i].z < map->z_min)
			map->z_min = map->cells[y][i].z;
		if (map->cells[y][i].z > map->z_max)
			map->z_max = map->cells[y][i].z;
		if (color - 1)
			map->cells[y][i].color = ft_atoi_base(z[1] + 2, 16); //hardcored jump of 0x
		else
			map->cells[y][i].color = 0; //default color
		i++;
		ft_free(color, (void **)z);
	}
}

/*
 * Fill the cells of the map with the values from the file
 */
void	fill_cells(t_map *map, char **argv)
{
	int		fd;
	char	*line;
	int		x;
	int		y;
	char	**x_values;

	y = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_perror("No file", 1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		x_values = ft_split(clean(line), ' ', &x);
		free(line);
		if (!x_values)
		{
			close(fd);
			ft_free(x, (void **)x_values);
			ft_perror("ft_split error", 1);
		}
		insert_values(map, x_values, y);
		ft_free(x, (void **)x_values);
		y++;
	}
	close(fd);
}

/*
 * Initialize the img struct with the values from the map
 */
void init_img(t_img *img, t_map *map)
{
	int h;
	int i;

	i = -1;
	img->x = map->x;
	img->y = map->y;
	img->pixels = (t_pixel **)malloc(sizeof(t_pixel *) * img->y);
	if (!img->pixels)
		ft_perror("Malloc error for img->pixels", 1); //free map? free img?
	while (++i < img->y)
	{
		h = -1;
		img->pixels[i] = (t_pixel *)malloc(sizeof(t_pixel) * img->x);
		if (!img->pixels[i])
		{
			ft_free(i, (void **)img->pixels);
			ft_perror("Malloc error for a pixels row", 1);
		}
		while (++h < img->x)
			img->pixels[i][h].color = map->cells[i][h].color;
	}
}
