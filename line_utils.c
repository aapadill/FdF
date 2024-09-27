/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:07:13 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/27 15:07:18 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//change naming to argb
uint8_t		get_r(uint32_t rgba)
{
    //return ((rgba >> 24) & 0xFF);
    return ((rgba >> 16) & 0xFF);
}

uint8_t		get_g(uint32_t rgba)
{
	//return ((rgba >> 16) & 0xFF);
	return ((rgba >> 8) & 0xFF);
}

uint8_t		get_b(uint32_t rgba)
{
	//return ((rgba >> 8) & 0xFF);
	return (rgba & 0xFF);
}

uint8_t		get_a(uint32_t rgba)
{
	//return (rgba & 0xFF);
	return ((rgba >> 24) & 0xFF);
}

uint32_t	get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
	//return (r << 16 | g << 8 | b);
	//return (a << 24 | r << 16 | g << 8 | b);
}