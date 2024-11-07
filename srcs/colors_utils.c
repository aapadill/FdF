/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:20:34 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/27 17:20:36 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

uint8_t	get_r(uint32_t rgba)
{
	return ((rgba >> 16) & 0xFF);
}

uint8_t	get_g(uint32_t rgba)
{
	return ((rgba >> 8) & 0xFF);
}

uint8_t	get_b(uint32_t rgba)
{
	return (rgba & 0xFF);
}

uint8_t	get_a(uint32_t rgba)
{
	return ((rgba >> 24) & 0xFF);
}

uint32_t	get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
