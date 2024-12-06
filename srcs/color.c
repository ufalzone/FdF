/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:45:45 by ufalzone          #+#    #+#             */
/*   Updated: 2024/12/06 18:02:14 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// Obtenir la couleur en fonction de la valeur
int	get_color(t_map *map, int value)
{
	float	normalized_value;
	int		colors[11];
	int		index;

	colors[0] = 0xFFDAB9;
	colors[1] = 0xFFB6C1;
	colors[2] = 0xFFA07A;
	colors[3] = 0xFF8C69;
	colors[4] = 0xFF69B4;
	colors[5] = 0xFF1493;
	colors[6] = 0xDA70D6;
	colors[7] = 0xBA55D3;
	colors[8] = 0x9370DB;
	colors[9] = 0x8A2BE2;
	colors[10] = 0x800080;
	if (map->z_max == map->z_min)
		return (colors[0]);
	normalized_value = (float)(value - map->z_min) / (map->z_max - map->z_min);
	index = (int)(normalized_value * 10);
	if (index > 10)
		index = 10;
	return (colors[index]);
}
