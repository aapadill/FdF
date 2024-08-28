/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:40:45 by aapadill          #+#    #+#             */
/*   Updated: 2024/08/29 01:52:04 by aapadill         ###   ########.fr       */
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
		//ft_split(line, ' ', &words);
		//while (*values_x)
		//	ft_printf("\t%s", *values_x++);
		//ft_printf("\n");
		if (y == 0)
			x = words - (*values_x[words-1] == '\n');
		else
			if (x != words - (*values_x[words-1] == '\n'))
				ft_perror("Map error", 0);
		ft_printf("x: %i\n", x);
		y++;
		line = get_next_line(fd);
	}
	//if (y != x)
	//	ft_perror("Map error", 0);
	printf("x: %i, y: %i\n", x, y);
	return(1); //valid
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
