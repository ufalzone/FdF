/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 20:47:11 by ufalzone          #+#    #+#             */
/*   Updated: 2024/12/03 22:59:20 by ufalzone         ###   ########.fr       */
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

#ifndef WEIGHT
# define WEIGHT 1000
#endif

#ifndef HEIGHT
# define HEIGHT 1000
#endif

typedef struct s_point
{
	int		 x; // Position X
	int		 y; // Position Y
	int		 z; // Altitude
	int			 color; // Couleur
}	t_point;

typedef struct s_map
{
	int width;      // Nombre de colonnes (largeur)
	int height;     // Nombre de lignes (hauteur)
	t_point **grid; // Tableau 2D de points
	int		z_min;			// Valeur minimale de l'altitude
	int		z_max;			// Valeur maximale de l'altitude
}	t_map;

typedef struct s_fdf {
    void    *mlx;       // Pointeur MLX
    void    *win;       // Fenêtre MLX
    t_map   map;        // La carte (déjà définie)
    int     zoom;       // Facteur de zoom
    int     offset_x;   // Décalage horizontal
    int     offset_y;   // Décalage vertical
	int		is_right_clicked;	// Booléen pour savoir si le bouton droit est cliqué
	int		last_x;		// Position X du dernier clic droit
	int		last_y;		// Position Y du dernier clic droit
	int		is_left_clicked;	// Booléen pour savoir si le bouton gauche est cliqué
	int		last_x_left;	// Position X du dernier clic gauche
	int		last_y_left;	// Position Y du dernier clic gauche
	int		angle_iso;		// Angle de projection isométrique
	float		angle_z;		// Angle de rotation en Z
	float		angle_x;		// Angle de rotation en X
	float		angle_y;		// Angle de rotation en Y
	int		z_divisor;		// Diviseur de l'altitude
	int	projection_type;	// Type de projection (0 = iso, 1 = perspective)

}	t_fdf;


t_map	parse_map(char *filename);
int		get_color(int x);
#endif