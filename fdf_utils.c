/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:29:19 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/20 15:51:13 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mlx_perror(void)
{
	ft_putendl_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int	ft_perror(char *error_msg, int is_syscall)
{
	if (is_syscall)
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	if (error_msg)
		ft_putendl_fd(error_msg, STDERR_FILENO);
	//free
	exit(EXIT_FAILURE);
}

void	ft_free(int n, void **ptr_array)
{
	while (n--)
		free(ptr_array[n]);
	free(ptr_array);
}
