/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:40:45 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/08 15:42:58 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 * Checks if each of the z values has only two values (z (integer) and a color)
 * improv: Close fd if (!z)?
 */
void	validate_values(char **values, int n, int fd)
{
	char	**z;
	int		color;
	int		i;

	i = 0;
	while (i < n)
	{
		z = gc_split(values[i], ',', &color);
		if (!z)
		{
			gc_next_line(fd, CLEAN_LINE);
			gc_perror("Malloc error (z split)", 1);
		}
		if (color < 1 || color > 2 || int_overflows(z[0]))
		{
			gc_next_line(fd, CLEAN_LINE);
			gc_perror("Values format error", 0);
		}
		gc_free_array(color, (void **)z);
		i++;
	}
}

/*
 * Validates the line from the file
 * Checks if the values are integers and if dimension of the map is consistent
 */
void	validate_line(char *line, int *x, int *y, int fd)
{
	int		values;
	char	**splitted_line;

	splitted_line = gc_split(clean(line), ' ', &values);
	gc_free(line);
	if (!splitted_line)
	{
		close(fd);
		gc_perror("Malloc error (x split)", 1);
	}
	validate_values(splitted_line, values, fd);
	if (!*y)
		*x = values;
	else if (*x != values)
	{
		close(fd);
		gc_perror("Map error (your file is missing some x values)", 0);
	}
	(*y)++;
	gc_free_array(values, (void **)splitted_line);
}

/*
 * Validate the file, if valid, returns a 2D array of cells
 */
t_cell	**validate_file(char **argv, int *x, int *y)
{
	int		fd;
	char	*line;
	int		file_n_size;

	file_n_size = ft_strlen(argv[1]);
	if (file_n_size < 5 || ft_strncmp(argv[1] + file_n_size - 4, ".fdf", 4))
		gc_perror("Invalid file extension", 0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		gc_perror("No file", 1);
	while (1)
	{
		line = gc_next_line(fd, READ_LINE);
		if (!line)
			break ;
		validate_line(line, x, y, fd);
	}
	close(fd);
	if (!*x || !*y)
		gc_perror("Empty file", 0);
	return (init_cells(*x, *y));
}

/*
 * Wrap points/cells using the (x, y, z, color) values from the file
 * and insert them into the map cells array
 * x, y, z, color (0 if not specified)
 * improv: Close fd if (!z)
 * improv: avoid hardcored jump of 2 (because of 0x) at ft_atoi_base
 */
void	insert_values(t_map	*map, char **x_values, int y)
{
	int		i;
	char	**z;
	int		color;

	i = 0;
	while (x_values[i])
	{
		z = gc_split(x_values[i], ',', &color);
		if (!z)
			gc_perror("Malloc error (z split)", 1);
		map->cells[y][i].x = i;
		map->cells[y][i].y = y;
		map->cells[y][i].z = ft_atoi(z[0]);
		if (color - 1)
			map->cells[y][i].color = ft_atoi_base(z[1] + 2, 16);
		else
			map->cells[y][i].color = 0;
		i++;
		gc_free_array(color, (void **)z);
	}
}

/*
 * Fill the cells of the map with the values from the file
 */
void	fill_cells(t_map *map, char **argv)
{
	int		fd;
	char	*line;
	int		y;

	y = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		gc_perror("No file", 1);
	while (1)
	{
		line = gc_next_line(fd, READ_LINE);
		if (!line)
			break ;
		fill_cells_helper(map, line, fd, y);
		y++;
	}
	close(fd);
}
