/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:48:15 by polmarti          #+#    #+#             */
/*   Updated: 2024/06/15 17:48:17 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Reverses the bytes of a 32-bit integer.
 * Takes an integer and swaps its bytes to convert between 
 * little-endian and big-endian formats.
 *
 * @param c The 32-bit integer whose bytes are to be reversed.
 * @return The 32-bit integer with its bytes reversed.
 */
int	reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}