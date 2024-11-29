/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 20:47:11 by ufalzone          #+#    #+#             */
/*   Updated: 2024/11/29 23:07:45 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>

typedef struct s_point
{
	int x; // Position X
	int y; // Position Y
	int z; // Altitude
	int color; // Couleur
}	t_point;

typedef struct s_map
{
	int width;      // Nombre de colonnes (largeur)
	int height;     // Nombre de lignes (hauteur)
	t_point **grid; // Tableau 2D de points
}	t_map;


t_map	parse_map(char *filename);

#endif