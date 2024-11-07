/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:22:20 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/07 13:55:48 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 * Reaches the end of an array of pointers
 */
void	ft_reach_end(int n, void **ptr_array)
{
	while (ptr_array[++n])
		;
}

/*
 * Replaces newline character and last spaces from a string with '\0'
 */
char	*clean(char *line)
{
	char	*next_line;
	int		len;

	next_line = ft_strchr(line, '\n');
	if (next_line)
		*next_line = '\0';
	len = ft_strlen(line);
	while (len && line[len - 1] == ' ')
	{
		line[len - 1] = '\0';
		len--;
	}
	return (line);
}

/*
 * Helper function for fill_cells
 */
void	fill_cells_helper(t_map *map, char *line, int fd, int y)
{
	int		x;
	char	**x_values;

	x_values = ft_split(clean(line), ' ', &x);
	free(line);
	if (!x_values)
	{
		close(fd);
		ft_free(map->y, (void **)map->cells);
		ft_perror("ft_split error", 1);
	}
	insert_values(map, x_values, y);
	ft_free(x, (void **)x_values);
}

/*
 * Allocates memory for the cells of a map
 */
t_cell	**init_cells(int x, int y)
{
	t_cell	**cells;
	int		i;

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
 * Initialize the img with the values of the map.
 * mins, maxs, width and height are initialized later on 
 * at the end of the projection with update_img_info()
 * improv: free map, free img before perror
 */
void	init_img(t_img *img, t_map *map)
{
	int	h;
	int	i;

	i = -1;
	img->x = map->x;
	img->y = map->y;
	img->pixels = (t_pixel **)malloc(sizeof(t_pixel *) * img->y);
	if (!img->pixels)
		ft_perror("Malloc error for img->pixels", 1);
	while (++i < img->y)
	{
		img->pixels[i] = (t_pixel *)malloc(sizeof(t_pixel) * img->x);
		if (!img->pixels[i])
		{
			ft_free(i, (void **)img->pixels);
			ft_perror("Malloc error for a pixels row", 1);
		}
		h = -1;
		while (++h < img->x)
			img->pixels[i][h].color = map->cells[i][h].color;
	}
}
