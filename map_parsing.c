/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:40:45 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/09 14:15:06 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_cell	**init_map(int x, int y)
{
	t_cell	**map;
	int i;

	i = 0;
	map = (t_cell **)malloc(sizeof(t_cell *) * y);
	if (!map)
		ft_perror("Malloc error for map", 1);
	while (i < y)
	{
		map[i] = (t_cell *)malloc(sizeof(t_cell) * x);
		if (!map[i])
		{
			while (--i >= 0)
				free(map[i]);
			free(map);
			ft_perror("Malloc error for a row", 1);
		}
		//you could technically also insert initial values here (zeros?)
		i++;
	}
	return (map);
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
	//int		prev;

	//prev = 0;
	while (*values)
	{
		z = ft_split(*values++, ',', &color);
		if (!z)
			ft_perror("Malloc error (z split)", 1);
		if (color < 1 || color > 2 || int_overflows(z[0]))
			ft_perror("Values format error", 0);
		//if (!prev)
		//	prev = color;
		//else if (prev != color)
		//	ft_perror("Inconsistent color channel values", 0);
		//if you had a map, you could technically insert values here
	}
	return (color - 1);
}

t_cell	**validate_map(char **argv, int *x, int *y)
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
			ft_perror("Map error (your map is missing some x values)", 0);
		(*y)++;
	}
	close(fd);
	return (init_map(*x, *y));
}

int	insert_values(t_cell **map, char **x_values, int y)
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
		map[y][i].z = ft_atoi(z[0]);
		if (color - 1)
			map[y][i].color = ft_atoi_base(z[1] + 2, 16); //hardcored jump of 0x
		else
			map[y][i].color = 4294967295; //default color
		i++;
	}
	return (1);
}

void	fill_map(t_cell **map, char **argv)
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
