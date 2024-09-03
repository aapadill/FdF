/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:31:03 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/03 13:47:27 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void print_map(t_cell **map, int x, int y)
{
	int j;
	int i;

	j = -1;
	while (++j < y)
	{
		printf("\n");
		i = -1;
		while (++i < x)
			printf("%li ", map[j][i].alpha);
	}
}

int main(int argc, char **argv)
{
	int		x;
	int		y;
	t_cell	**map;

	x = 0; //erasable
	y = 0;
	if (argc != 2)
		ft_perror("No valid arguments", 0);
	map = validate_map(argv, &x, &y);
	fill_map(map, argv);
	print_map(map, x, y);
	return (1);
}
