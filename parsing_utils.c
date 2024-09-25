/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:22:20 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/24 18:22:22 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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