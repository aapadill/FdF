/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:25:49 by aapadill          #+#    #+#             */
/*   Updated: 2024/08/31 17:56:54 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "ft_printf/include/ft_printf.h"
# include <fcntl.h>
# include <stdio.h> //erase
# include <errno.h>
# include <string.h>
# include <stdint.h> //erase?

typedef struct s_cell
{
	int z;
	int alpha;
}	t_cell;

#endif
