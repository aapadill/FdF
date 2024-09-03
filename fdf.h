/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:25:49 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/03 13:38:50 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "ft_printf/include/ft_printf.h"
# include <fcntl.h>
# include <stdio.h> //erase, grep printf
# include <errno.h>
# include <string.h>
# include <stdint.h> //erase?

typedef struct s_cell
{
	int z;
	long alpha;
}	t_cell;

int		ft_perror(char *error_msg, int is_syscall);
char	*clean(char *line);

t_cell	**init_map(int x, int y);
int		validate_values(char **values);
t_cell	**validate_map(char **argv, int *x, int *y);
int		insert_values(t_cell **map, char **x_values, int y);
void	fill_map(t_cell **map, char **argv);

#endif
