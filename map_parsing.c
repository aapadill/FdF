/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:40:45 by aapadill          #+#    #+#             */
/*   Updated: 2024/08/30 16:37:06 by aapadill         ###   ########.fr       */
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

int	validate_map_values(char **values)
{
	char	**x;
	int		alpha;
	//int		counter;

	//counter = 0;
	while (*values)
	{
		//counter++;
		x = ft_split(*values++, ',', &alpha);
		if (alpha < 1 || alpha > 2 || int_overflows(x[0]))
			ft_perror("Values error", 0);
		//printf("\n");
		//printf("%s, elem: %i", x[0], counter);
		//if (alpha == 2)
			//printf("\t%s", x[1]);
	}
	return (1);
}

void	clean(char *line)
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
}

int	validate_map_dimension(int fd)
{
	char	*line;
	int		words;
	int		x;
	int		y;
	char	**values_x;

	y = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		clean(line);
		values_x = ft_split(line, ' ', &words);
		validate_map_values(values_x);
		//printf("\n--next-y-value--");
		if (y == 0)
			x = words;
		else
			if (x != words)
				ft_perror("Map error", 0);
		y++;
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
