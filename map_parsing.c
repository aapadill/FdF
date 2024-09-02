/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:40:45 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/02 18:09:25 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_perror(char *error_msg, int is_syscall)
{
	if (is_syscall)
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	if (error_msg)
		ft_putendl_fd(error_msg, STDERR_FILENO);
	//free
	exit(EXIT_FAILURE);
}

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
		//you can insert 0 values here
		i++;
	}
	return (map);
}

int	validate_values(char **values)
{
	char	**z;
	int		alpha;
	int		prev;

	prev = 0;
	while (*values)
	{
		z = ft_split(*values++, ',', &alpha);
		if (!z)
			ft_perror("Malloc error", 1);
		if (alpha < 1 || alpha > 2 || int_overflows(z[0]))
			ft_perror("Values format error", 0);
		if (!prev)
			prev = alpha;
		else if (prev != alpha)
			ft_perror("Inconsistent alpha channel values", 0);
		//if you had a map, you could technically insert values here
	}
	return (alpha - 1);
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
			ft_perror("ft_split error", 1);
		validate_values(splitted_line); //returns alpha
		if (!*y)
			*x = values;
		else if (*x != values)
			ft_perror("Map error", 0);
		(*y)++;
	}
	close(fd);
	return (init_map(*x, *y));
}

int	insert_values(t_cell **map, char **x_values, int y)
{
	int		i;
	char	**z;
	int		alpha;

	i = 0;
	while (x_values[i])
	{
		z = ft_split(x_values[i], ',', &alpha);
		if (!z)
			ft_perror("Malloc error", 1);
		map[y][i].z = ft_atoi(z[0]);
		if (alpha - 1) //1 -> z value, 2 -> alpha value
			map[y][i].alpha = ft_atoi(z[1]); //atoi base 16?
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
	int j = -1;
	while (++j < y)
	{
		printf("\n");
		int i = -1;
		while (++i < x)
			printf("%i ", map[j][i].z);
	}
	return (1);
}
