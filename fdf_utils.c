/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:29:19 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/03 13:31:43 by aapadill         ###   ########.fr       */
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
