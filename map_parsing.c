/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:40:45 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/12 02:14:14 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	int	validate_values(char **values)
{
	char	**z;
	int		color;

	while (*values)
	{
		z = ft_split(*values++, ',', &color);
		if (!z)
			ft_perror("Malloc error (z split)", 1); //free values[i], free values
		if (color < 1 || color > 2 || int_overflows(z[0]))
			ft_perror("Values format error", 0); //free values[i], free values, free z
	}
	return (color - 1);
}

static	t_cell	**init_cells(int x, int y)
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
		if (!splitted_line)
			ft_perror("Malloc error (x split)", 1); //free line //close fd
		validate_values(splitted_line);
		if (!*y)
			*x = values;
		else if (*x != values) //free line //close fd //free splitted_line
			ft_perror("Map error (your file is missing some x values)", 0);
		(*y)++;
	}
	close(fd); //free line //free splitted_line
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
		if (!z) //while(--i) free(x_values[i]); free(x_values);
			ft_perror("Malloc error (z split)", 1);
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
		//free(z[0], z[1])? free(z);
	}
	//while(--i) free(x_values[i]);?
	//free(x_values);
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
		ft_perror("No file", 1); //close fd
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		x_values = ft_split(clean(line), ' ', &x);
		free(line);
		if (!x_values)
			ft_perror("ft_split error", 1); //close fd
		insert_values(map, x_values, y);
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
		ft_perror("Malloc error for img->pixels", 1); //free img //free map?
	while (++i < img->y)
	{
		h = -1;
		img->pixels[i] = (t_pixel *)malloc(sizeof(t_pixel) * img->x);
		if (!img->pixels[i])
		{
			while (--i >= 0)
				free(img->pixels[i]);
			free(img->pixels);
			ft_perror("Malloc error for a pixels row", 1);
		}
		while (++h < img->x)
			img->pixels[i][h].color = map->cells[i][h].color;
	}
}