/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:40:45 by aapadill          #+#    #+#             */
/*   Updated: 2024/08/29 13:29:28 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf/include/ft_printf.h"
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int	ft_perror(char *error_msg, int is_syscall)
{
	if (is_syscall)
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	else
		ft_putendl_fd(error_msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	print_argv(char **argv)
{
	while(*argv)
		ft_printf("\t%s", *argv++);
	ft_printf("\n");
}

int	validate_map_values(char **values)
{
	char	**x;
	int		alpha;
	int		counter;

	counter = 0;
	while (*values)
	{
		counter++;
		x = ft_split(*values++, ',', &alpha);
		if (alpha < 1 || alpha > 2)// || int_overflows(x[0]))
			ft_perror("Values error", 0);
		//if (*x[0] != '\n' && counter++)
		printf("\n");
		printf("%s, counter: %i", x[0], counter);
		if (alpha == 2)
			printf("\t%s", x[1]);
		//*values++;
	}
	return (1);
}

int	validate_map_dimension(int fd)
{
	char	*line;
	int		words;
	int		x;
	int		y;
	char	**values_x;

	y = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		values_x = ft_split(line, ' ', &words);
		validate_map_values(values_x);
		if (y == 0)
			x = words - (*values_x[words-1] == '\n');
		else
			if (x != words - (*values_x[words-1] == '\n'))
				ft_perror("Map error", 0);
		y++;
		line = get_next_line(fd);
	}
	printf("x: %i, y: %i\n", x, y);
	return (1);
}

int	validate_inputs(int argc, char **argv)
{
	int		fd;

	if (argc != 2)
		ft_perror("No valid arguments", 0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_perror("No file", 1);
	validate_map_dimension(fd);
	close(fd);
	return (1);
}

int main(int argc, char **argv)
{
	validate_inputs(argc, argv);
	return (1);
}
