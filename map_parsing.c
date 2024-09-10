/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:40:45 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/09 18:57:07 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_cell	**init_cells(int x, int y)
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
			while (--i >= 0)
				free(cells[i]);
			free(cells);
			ft_perror("Malloc error for a row", 1);
		}
		//you could technically also insert initial values here (zeros?)
		i++;
	}
	return (cells);
}

t_pixel	**init_img(int x, int y)
{
	t_pixel	**img;
	int i;

	i = 0;
	img = (t_pixel **)malloc(sizeof(t_pixel *) * y);
	if (!img)
		ft_perror("Malloc error for img", 1);
	while (i < y)
	{
		img[i] = (t_pixel *)malloc(sizeof(t_pixel) * x);
		if (!img[i])
		{
			while (--i >= 0)
				free(img[i]);
			free(img);
			ft_perror("Malloc error for a row", 1);
		}
		//you could technically also insert initial values here (zeros?)
		//initialize color channel maybe?
		i++;
	}
	return (img);
}

int	validate_values(char **values)
{
	char	**z;
	int		color;

	while (*values)
	{
		z = ft_split(*values++, ',', &color);
		if (!z)
			ft_perror("Malloc error (z split)", 1);
		if (color < 1 || color > 2 || int_overflows(z[0]))
			ft_perror("Values format error", 0);
		//if you had a map, you could technically insert values here
	}
	return (color - 1);
}

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
		if (!splitted_line)
			ft_perror("Malloc error (x split)", 1);
		validate_values(splitted_line); //returns color
		if (!*y)
			*x = values;
		else if (*x != values)
			ft_perror("Map error (your file is missing some x values)", 0);
		(*y)++;
	}
	close(fd);
	return (init_cells(*x, *y));
}

//int	insert_values(t_cell **cells, char **x_values, int y)
int	insert_values(t_map	*map, char **x_values, int y)
{
	int		i;
	char	**z;
	int		color;

	i = 0;
	while (x_values[i])
	{
		z = ft_split(x_values[i], ',', &color);
		if (!z)
			ft_perror("Malloc error (z split)", 1);
		map->cells[y][i].z = ft_atoi(z[0]);
		if (!i && !y)
		{
			map->z_min = map->cells[0][0].z;
			map->z_max = map->cells[0][0].z;
		}
		if (map->cells[y][i].z < map->z_min)
			map->z_min = map->cells[y][i].z;
		if (map->cells[y][i].z > map->z_min)
			map->z_min = map->cells[y][i].z;
		if (color - 1)
			map->cells[y][i].color = ft_atoi_base(z[1] + 2, 16); //hardcored jump of 0x
		else
			map->cells[y][i].color = 4294967295; //default color
		i++;
	}
	return (1);
}

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
		if (!x_values)
			ft_perror("ft_split error", 1);
		insert_values(map, x_values, y);
		y++;
	}
	close(fd);
}
