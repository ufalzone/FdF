/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:45:45 by ufalzone          #+#    #+#             */
/*   Updated: 2024/12/07 17:34:21 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// Obtenir la couleur en fonction de la valeur
int	get_color(t_map *map, int value)
{
	float	normalized_value;
	int		colors[11];
	int		index;

	colors[0] = 0xFF8000;
	colors[1] = 0xFF6B00;
	colors[2] = 0xFF5500;
	colors[3] = 0xFF4000;
	colors[4] = 0xFF2B00;
	colors[5] = 0xFF1500;
	colors[6] = 0xFF5555;
	colors[7] = 0xFF8888;
	colors[8] = 0xFFBBBB;
	colors[9] = 0xFFDDDD;
	colors[10] = 0xFFFFFF;
	if (map->z_max == map->z_min)
		return (colors[0]);
	normalized_value = (float)(value - map->z_min) / (map->z_max - map->z_min);
	index = (int)(normalized_value * 10);
	if (index > 10)
		index = 10;
	return (colors[index]);
}
