/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 10:25:43 by aapadill          #+#    #+#             */
/*   Updated: 2024/08/12 11:01:09 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

int main(void)
{
	void	*img;
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	img = mlx_new_image(mlx, 1920, 1080);
	mlx_win = mlx_new_window(mlx, 489, 480, "Hello World");
	mlx_loop(mlx);
}
